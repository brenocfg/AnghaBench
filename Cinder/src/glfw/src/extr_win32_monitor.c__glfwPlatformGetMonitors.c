#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _GLFWmonitor ;
struct TYPE_6__ {int cb; int StateFlags; int /*<<< orphan*/ * DeviceName; } ;
typedef  scalar_t__ GLFWbool ;
typedef  size_t DWORD ;
typedef  TYPE_1__ DISPLAY_DEVICEW ;

/* Variables and functions */
 int DISPLAY_DEVICE_ACTIVE ; 
 int DISPLAY_DEVICE_PRIMARY_DEVICE ; 
 scalar_t__ EnumDisplayDevicesW (int /*<<< orphan*/ *,size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GLFW_FALSE ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _GLFW_SWAP_POINTERS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * createMonitor (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 

_GLFWmonitor** _glfwPlatformGetMonitors(int* count)
{
    int found = 0;
    DWORD adapterIndex, displayIndex, primaryIndex = 0;
    DISPLAY_DEVICEW adapter, display;
    GLFWbool hasDisplays = GLFW_FALSE;
    _GLFWmonitor** monitors = NULL;

    *count = 0;

    // HACK: Check if any active adapters have connected displays
    //       If not, this is a headless system or a VMware guest

    for (adapterIndex = 0;  ;  adapterIndex++)
    {
        ZeroMemory(&adapter, sizeof(DISPLAY_DEVICEW));
        adapter.cb = sizeof(DISPLAY_DEVICEW);

        if (!EnumDisplayDevicesW(NULL, adapterIndex, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        ZeroMemory(&display, sizeof(DISPLAY_DEVICEW));
        display.cb = sizeof(DISPLAY_DEVICEW);

        if (EnumDisplayDevicesW(adapter.DeviceName, 0, &display, 0))
        {
            hasDisplays = GLFW_TRUE;
            break;
        }
    }

    for (adapterIndex = 0;  ;  adapterIndex++)
    {
        ZeroMemory(&adapter, sizeof(DISPLAY_DEVICEW));
        adapter.cb = sizeof(DISPLAY_DEVICEW);

        if (!EnumDisplayDevicesW(NULL, adapterIndex, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        if (adapter.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
            primaryIndex = found;

        if (hasDisplays)
        {
            for (displayIndex = 0;  ;  displayIndex++)
            {
                ZeroMemory(&display, sizeof(DISPLAY_DEVICEW));
                display.cb = sizeof(DISPLAY_DEVICEW);

                if (!EnumDisplayDevicesW(adapter.DeviceName, displayIndex, &display, 0))
                    break;

                found++;
                monitors = realloc(monitors, sizeof(_GLFWmonitor*) * found);
                monitors[found - 1] = createMonitor(&adapter, &display);
            }
        }
        else
        {
            found++;
            monitors = realloc(monitors, sizeof(_GLFWmonitor*) * found);
            monitors[found - 1] = createMonitor(&adapter, NULL);
        }
    }

    _GLFW_SWAP_POINTERS(monitors[0], monitors[primaryIndex]);

    *count = found;
    return monitors;
}