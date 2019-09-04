#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ surface; scalar_t__ shell_surface; scalar_t__ native; } ;
struct TYPE_11__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_10__ {TYPE_3__* keyboardFocus; TYPE_3__* pointerFocus; } ;
struct TYPE_12__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwDestroyContext (TYPE_3__*) ; 
 int /*<<< orphan*/  _glfwInputCursorEnter (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowFocus (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_egl_window_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_surface_destroy (scalar_t__) ; 

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
    if (window == _glfw.wl.pointerFocus)
    {
        _glfw.wl.pointerFocus = NULL;
        _glfwInputCursorEnter(window, GL_FALSE);
    }
    if (window == _glfw.wl.keyboardFocus)
    {
        _glfw.wl.keyboardFocus = NULL;
        _glfwInputWindowFocus(window, GL_FALSE);
    }

    _glfwDestroyContext(window);

    if (window->wl.native)
        wl_egl_window_destroy(window->wl.native);

    if (window->wl.shell_surface)
        wl_shell_surface_destroy(window->wl.shell_surface);

    if (window->wl.surface)
        wl_surface_destroy(window->wl.surface);
}