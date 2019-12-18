#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * monitor; struct TYPE_7__* next; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWmonitor ;
struct TYPE_6__ {int /*<<< orphan*/  (* monitor ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int monitorCount; int /*<<< orphan*/ ** monitors; TYPE_1__ callbacks; TYPE_2__* windowListHead; } ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CONNECTED ; 
 int /*<<< orphan*/  GLFW_DISCONNECTED ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwFreeMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwFreeMonitors (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** _glfwPlatformGetMonitors (int*) ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_2__*,int*,int*) ; 
 scalar_t__ _glfwPlatformIsSameMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowMonitor (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _glfwInputMonitorChange(void)
{
    int i, j, monitorCount = _glfw.monitorCount;
    _GLFWmonitor** monitors = _glfw.monitors;

    _glfw.monitors = _glfwPlatformGetMonitors(&_glfw.monitorCount);

    // Re-use still connected monitor objects

    for (i = 0;  i < _glfw.monitorCount;  i++)
    {
        for (j = 0;  j < monitorCount;  j++)
        {
            if (_glfwPlatformIsSameMonitor(_glfw.monitors[i], monitors[j]))
            {
                _glfwFreeMonitor(_glfw.monitors[i]);
                _glfw.monitors[i] = monitors[j];
                break;
            }
        }
    }

    // Find and report disconnected monitors (not in the new list)

    for (i = 0;  i < monitorCount;  i++)
    {
        _GLFWwindow* window;

        for (j = 0;  j < _glfw.monitorCount;  j++)
        {
            if (monitors[i] == _glfw.monitors[j])
                break;
        }

        if (j < _glfw.monitorCount)
            continue;

        for (window = _glfw.windowListHead;  window;  window = window->next)
        {
            if (window->monitor == monitors[i])
            {
                int width, height;
                _glfwPlatformGetWindowSize(window, &width, &height);
                _glfwPlatformSetWindowMonitor(window, NULL, 0, 0, width, height, 0);
            }
        }

        if (_glfw.callbacks.monitor)
            _glfw.callbacks.monitor((GLFWmonitor*) monitors[i], GLFW_DISCONNECTED);
    }

    // Find and report newly connected monitors (not in the old list)
    // Re-used monitor objects are then removed from the old list to avoid
    // having them destroyed at the end of this function

    for (i = 0;  i < _glfw.monitorCount;  i++)
    {
        for (j = 0;  j < monitorCount;  j++)
        {
            if (_glfw.monitors[i] == monitors[j])
            {
                monitors[j] = NULL;
                break;
            }
        }

        if (j < monitorCount)
            continue;

        if (_glfw.callbacks.monitor)
            _glfw.callbacks.monitor((GLFWmonitor*) _glfw.monitors[i], GLFW_CONNECTED);
    }

    _glfwFreeMonitors(monitors, monitorCount);
}