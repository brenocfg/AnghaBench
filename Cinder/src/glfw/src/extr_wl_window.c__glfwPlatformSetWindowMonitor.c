#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  shell_surface; } ;
struct TYPE_11__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  output; } ;
struct TYPE_12__ {TYPE_1__ wl; } ;
typedef  TYPE_4__ _GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT ; 
 int /*<<< orphan*/  _glfwInputWindowMonitorChange (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  wl_shell_surface_set_fullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (int /*<<< orphan*/ ) ; 

void _glfwPlatformSetWindowMonitor(_GLFWwindow* window,
                                   _GLFWmonitor* monitor,
                                   int xpos, int ypos,
                                   int width, int height,
                                   int refreshRate)
{
    if (monitor)
    {
        wl_shell_surface_set_fullscreen(
            window->wl.shell_surface,
            WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,
            refreshRate * 1000, // Convert Hz to mHz.
            monitor->wl.output);
    }
    else
    {
        wl_shell_surface_set_toplevel(window->wl.shell_surface);
    }
    _glfwInputWindowMonitorChange(window, monitor);
}