#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* monitor; } ;
typedef  TYPE_4__ _GLFWwndconfig ;
struct TYPE_13__ {int /*<<< orphan*/ * currentCursor; int /*<<< orphan*/  shell_surface; } ;
struct TYPE_15__ {TYPE_3__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
typedef  int /*<<< orphan*/  _GLFWctxconfig ;
struct TYPE_11__ {int /*<<< orphan*/  output; } ;
struct TYPE_12__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT ; 
 int /*<<< orphan*/  _glfwCreateContext (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  createSurface (TYPE_5__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  wl_shell_surface_set_fullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (int /*<<< orphan*/ ) ; 

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GL_FALSE;

    if (!createSurface(window, wndconfig))
        return GL_FALSE;

    if (wndconfig->monitor)
    {
        wl_shell_surface_set_fullscreen(
            window->wl.shell_surface,
            WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,
            0,
            wndconfig->monitor->wl.output);
    }
    else
    {
        wl_shell_surface_set_toplevel(window->wl.shell_surface);
    }

    window->wl.currentCursor = NULL;

    return GL_TRUE;
}