#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  monitors; int /*<<< orphan*/  title; scalar_t__ surface; scalar_t__ shell_surface; scalar_t__ native; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;
struct TYPE_13__ {TYPE_3__ wl; TYPE_2__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_10__ {TYPE_4__* keyboardFocus; TYPE_4__* pointerFocus; } ;
struct TYPE_14__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwInputCursorEnter (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowFocus (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  wl_egl_window_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_surface_destroy (scalar_t__) ; 

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
    if (window == _glfw.wl.pointerFocus)
    {
        _glfw.wl.pointerFocus = NULL;
        _glfwInputCursorEnter(window, GLFW_FALSE);
    }
    if (window == _glfw.wl.keyboardFocus)
    {
        _glfw.wl.keyboardFocus = NULL;
        _glfwInputWindowFocus(window, GLFW_FALSE);
    }

    if (window->context.destroy)
        window->context.destroy(window);

    if (window->wl.native)
        wl_egl_window_destroy(window->wl.native);

    if (window->wl.shell_surface)
        wl_shell_surface_destroy(window->wl.shell_surface);

    if (window->wl.surface)
        wl_surface_destroy(window->wl.surface);

    free(window->wl.title);
    free(window->wl.monitors);
}