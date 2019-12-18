#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ maximized; scalar_t__ shell_surface; } ;
struct TYPE_5__ {TYPE_1__ wl; scalar_t__ monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (scalar_t__) ; 

void _glfwPlatformRestoreWindow(_GLFWwindow* window)
{
    // TODO: also do the same for iconified.
    if (window->monitor || window->wl.maximized)
    {
        if (window->wl.shell_surface)
            wl_shell_surface_set_toplevel(window->wl.shell_surface);

        window->wl.maximized = GLFW_FALSE;
    }
}