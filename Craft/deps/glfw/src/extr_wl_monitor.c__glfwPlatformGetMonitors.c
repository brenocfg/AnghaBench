#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  modesCount; } ;
struct TYPE_9__ {TYPE_1__ wl; int /*<<< orphan*/  modes; } ;
typedef  TYPE_3__ _GLFWmonitor ;
struct TYPE_8__ {int monitorsCount; TYPE_3__** monitors; } ;
struct TYPE_10__ {TYPE_2__ wl; } ;

/* Variables and functions */
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoModes (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* calloc (int,int) ; 

_GLFWmonitor** _glfwPlatformGetMonitors(int* count)
{
    _GLFWmonitor** monitors;
    _GLFWmonitor* monitor;
    int i, monitorsCount = _glfw.wl.monitorsCount;

    if (_glfw.wl.monitorsCount == 0)
        goto err;

    monitors = calloc(monitorsCount, sizeof(_GLFWmonitor*));

    for (i = 0; i < monitorsCount; i++)
    {
        _GLFWmonitor* origMonitor = _glfw.wl.monitors[i];
        monitor = calloc(1, sizeof(_GLFWmonitor));

        monitor->modes =
            _glfwPlatformGetVideoModes(origMonitor,
                                       &origMonitor->wl.modesCount);
        *monitor = *_glfw.wl.monitors[i];
        monitors[i] = monitor;
    }

    *count = monitorsCount;
    return monitors;

err:
    *count = 0;
    return NULL;
}