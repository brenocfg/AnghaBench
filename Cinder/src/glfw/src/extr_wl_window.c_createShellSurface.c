#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  shell_surface; scalar_t__ maximized; scalar_t__ title; int /*<<< orphan*/  surface; } ;
struct TYPE_13__ {TYPE_4__ wl; TYPE_3__* monitor; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  shell; } ;
struct TYPE_14__ {TYPE_1__ wl; } ;
struct TYPE_10__ {int /*<<< orphan*/  output; } ;
struct TYPE_11__ {TYPE_2__ wl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  shellSurfaceListener ; 
 int /*<<< orphan*/  wl_shell_get_shell_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shell_surface_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  wl_shell_surface_set_fullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shell_surface_set_maximized (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_shell_surface_set_title (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLFWbool createShellSurface(_GLFWwindow* window)
{
    window->wl.shell_surface = wl_shell_get_shell_surface(_glfw.wl.shell,
                                                          window->wl.surface);
    if (!window->wl.shell_surface)
        return GLFW_FALSE;

    wl_shell_surface_add_listener(window->wl.shell_surface,
                                  &shellSurfaceListener,
                                  window);

    if (window->wl.title)
        wl_shell_surface_set_title(window->wl.shell_surface, window->wl.title);

    if (window->monitor)
    {
        wl_shell_surface_set_fullscreen(
            window->wl.shell_surface,
            WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,
            0,
            window->monitor->wl.output);
    }
    else if (window->wl.maximized)
    {
        wl_shell_surface_set_maximized(window->wl.shell_surface, NULL);
    }
    else
    {
        wl_shell_surface_set_toplevel(window->wl.shell_surface);
    }

    return GLFW_TRUE;
}