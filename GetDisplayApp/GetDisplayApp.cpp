#include <Windows.h>
#include <stdio.h>

void PrintDisplayDevice(DISPLAY_DEVICEA* displayDevice, const char* indent = "")
{
    printf("%sDeviceName: %s\n", indent, displayDevice->DeviceName);
    //printf("%sDeviceString: %s\n", indent, displayDevice->DeviceString);
    printf("%sStateFlags:", indent);
    if (displayDevice->StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) { printf("**THIS IS THE PRIMARY PRIMARY_DEVICE**"); }
    if (displayDevice->StateFlags & DISPLAY_DEVICE_ACTIVE) { printf ("DISPLAY_DEVICE_ACTIVE specifies whether a monitor is presented as being on by the respective GDI view.Windows Vista : EnumDisplayDevices will only enumerate monitors that can be presented as being on."); }
    //if (displayDevice->StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) { printf(" MIRRORING_DRIVER"); }
    //if (displayDevice->StateFlags & DISPLAY_DEVICE_MODESPRUNED) { printf(" MODESPRUNED"); }
    //if (displayDevice->StateFlags & DISPLAY_DEVICE_REMOVABLE) { printf(" REMOVABLE"); }
    //if (displayDevice->StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE) { printf(" VGA_COMPATIBLE"); }
    printf("\n");
    //printf("%sDeviceID: %s\n", indent, displayDevice->DeviceID);
}

void PrintDisplaySettings(DISPLAY_DEVICEA* displayDevice, const char* indent = "")
{
    int i = 0;
    DEVMODEA mode;
    mode.dmSize = sizeof(DEVMODEA);
    mode.dmDriverExtra = 0;

    while (EnumDisplaySettingsA(displayDevice->DeviceName, i, &mode))
    {
        printf("%s----- Display Mode %d -----\n", indent, i);
        printf("%sBitsPerPixel: %d\n", indent, mode.dmBitsPerPel);
        printf("%sWidth: %d\n", indent, mode.dmPelsWidth);
        printf("%sHeight: %d\n", indent, mode.dmPelsHeight);
        printf("%sFrequency: %d\n", indent, mode.dmDisplayFrequency);

        i++;
    }
    printf("%sTotal display modes: %d\n", indent, i);
}

void main()
{
    int i = 0;
    DISPLAY_DEVICEA displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICEA);

    while (EnumDisplayDevicesA(NULL, i, &displayDevice, 0))
    {
        printf("======= Display Device %d =======\n", i);
        PrintDisplayDevice(&displayDevice);
        // PrintDisplaySettings(&displayDevice, "\t");

        int j = 0;
        DISPLAY_DEVICEA displayDevice2;
        displayDevice2.cb = sizeof(DISPLAY_DEVICEA);
        while (EnumDisplayDevicesA(displayDevice.DeviceName, j, &displayDevice2, 0))
        {
            printf("\t======= Display Device %d,%d =======\n", i, j);
            PrintDisplayDevice(&displayDevice2, "\t");
            // PrintDisplaySettings(&displayDevice2, "\t\t");
            j++;
        }
        printf("\tTotal display outputs: %d\n", j);
        i++;
    }
    printf("Total display devices: %d\n", i);

    printf("Done.\n");
    printf("Press any key to quit... ");
    getchar();
}