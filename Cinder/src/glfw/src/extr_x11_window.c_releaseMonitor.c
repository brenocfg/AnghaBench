#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_9__ {scalar_t__ count; int /*<<< orphan*/  exposure; int /*<<< orphan*/  blanking; int /*<<< orphan*/  interval; int /*<<< orphan*/  timeout; } ;
struct TYPE_8__ {TYPE_2__ saver; int /*<<< orphan*/  display; } ;
struct TYPE_12__ {TYPE_1__ x11; } ;
struct TYPE_11__ {TYPE_3__* window; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSetScreenSaver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMonitorWindowChange (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwRestoreVideoModeX11 (TYPE_5__*) ; 

__attribute__((used)) static void releaseMonitor(_GLFWwindow* window)
{
    if (window->monitor->window != window)
        return;

    _glfwInputMonitorWindowChange(window->monitor, NULL);
    _glfwRestoreVideoModeX11(window->monitor);

    _glfw.x11.saver.count--;

    if (_glfw.x11.saver.count == 0)
    {
        // Restore old screen saver settings
        XSetScreenSaver(_glfw.x11.display,
                        _glfw.x11.saver.timeout,
                        _glfw.x11.saver.interval,
                        _glfw.x11.saver.blanking,
                        _glfw.x11.saver.exposure);
    }
}