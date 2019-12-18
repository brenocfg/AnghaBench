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
struct TYPE_5__ {TYPE_1__ wl; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  wl_shell_surface_set_maximized (scalar_t__,int /*<<< orphan*/ *) ; 

void _glfwPlatformMaximizeWindow(_GLFWwindow* window)
{
    if (!window->monitor && !window->wl.maximized)
    {
        if (window->wl.shell_surface)
        {
            // Let the compositor select the best output.
            wl_shell_surface_set_maximized(window->wl.shell_surface, NULL);
        }
        window->wl.maximized = GLFW_TRUE;
    }
}