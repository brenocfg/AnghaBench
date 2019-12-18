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
struct TYPE_4__ {int /*<<< orphan*/  visible; scalar_t__ shell_surface; } ;
struct TYPE_5__ {TYPE_1__ wl; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  wl_shell_surface_destroy (scalar_t__) ; 

void _glfwPlatformHideWindow(_GLFWwindow* window)
{
    if (!window->monitor)
    {
        if (window->wl.shell_surface)
            wl_shell_surface_destroy(window->wl.shell_surface);
        window->wl.visible = GLFW_FALSE;
    }
}