#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  publicDisplayName; int /*<<< orphan*/  publicAdapterName; int /*<<< orphan*/  displayName; int /*<<< orphan*/  adapterName; int /*<<< orphan*/  modesPruned; } ;
struct TYPE_13__ {TYPE_1__ win32; } ;
typedef  TYPE_2__ _GLFWmonitor ;
struct TYPE_14__ {int cb; int StateFlags; int /*<<< orphan*/ * DeviceName; int /*<<< orphan*/  DeviceString; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_3__ DISPLAY_DEVICEW ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CreateDCW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DISPLAY_DEVICE_ACTIVE ; 
 int DISPLAY_DEVICE_MODESPRUNED ; 
 int DISPLAY_DEVICE_PRIMARY_DEVICE ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnumDisplayDevicesW (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZSIZE ; 
 int /*<<< orphan*/  VERTSIZE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _GLFW_SWAP_POINTERS (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* _glfwAllocMonitor (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* _glfwCreateUTF8FromWideString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__** realloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

_GLFWmonitor** _glfwPlatformGetMonitors(int* count)
{
    int found = 0;
    _GLFWmonitor** monitors = NULL;
    DWORD adapterIndex, displayIndex;

    *count = 0;

    for (adapterIndex = 0;  ;  adapterIndex++)
    {
        DISPLAY_DEVICEW adapter;

        ZeroMemory(&adapter, sizeof(DISPLAY_DEVICEW));
        adapter.cb = sizeof(DISPLAY_DEVICEW);

        if (!EnumDisplayDevicesW(NULL, adapterIndex, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        for (displayIndex = 0;  ;  displayIndex++)
        {
            DISPLAY_DEVICEW display;
            _GLFWmonitor* monitor;
            char* name;
            HDC dc;

            ZeroMemory(&display, sizeof(DISPLAY_DEVICEW));
            display.cb = sizeof(DISPLAY_DEVICEW);

            if (!EnumDisplayDevicesW(adapter.DeviceName, displayIndex, &display, 0))
                break;

            name = _glfwCreateUTF8FromWideString(display.DeviceString);
            if (!name)
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "Win32: Failed to convert string to UTF-8");
                continue;
            }

            dc = CreateDCW(L"DISPLAY", adapter.DeviceName, NULL, NULL);

            monitor = _glfwAllocMonitor(name,
                                        GetDeviceCaps(dc, HORZSIZE),
                                        GetDeviceCaps(dc, VERTSIZE));

            DeleteDC(dc);
            free(name);

            if (adapter.StateFlags & DISPLAY_DEVICE_MODESPRUNED)
                monitor->win32.modesPruned = GL_TRUE;

            wcscpy(monitor->win32.adapterName, adapter.DeviceName);
            wcscpy(monitor->win32.displayName, display.DeviceName);

            WideCharToMultiByte(CP_UTF8, 0,
                                adapter.DeviceName, -1,
                                monitor->win32.publicAdapterName,
                                sizeof(monitor->win32.publicAdapterName),
                                NULL, NULL);

            WideCharToMultiByte(CP_UTF8, 0,
                                display.DeviceName, -1,
                                monitor->win32.publicDisplayName,
                                sizeof(monitor->win32.publicDisplayName),
                                NULL, NULL);

            found++;
            monitors = realloc(monitors, sizeof(_GLFWmonitor*) * found);
            monitors[found - 1] = monitor;

            if (adapter.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE &&
                displayIndex == 0)
            {
                _GLFW_SWAP_POINTERS(monitors[0], monitors[found - 1]);
            }
        }
    }

    *count = found;
    return monitors;
}