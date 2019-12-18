#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ visible; scalar_t__ title; } ;
typedef  TYPE_2__ _GLFWwndconfig ;
struct TYPE_13__ {int visible; int monitorsSize; scalar_t__ monitorsCount; int /*<<< orphan*/  monitors; int /*<<< orphan*/ * currentCursor; int /*<<< orphan*/ * shell_surface; int /*<<< orphan*/  title; } ;
struct TYPE_15__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWmonitor ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
struct TYPE_16__ {scalar_t__ client; } ;
typedef  TYPE_4__ _GLFWctxconfig ;

/* Variables and functions */
 int GLFW_FALSE ; 
 scalar_t__ GLFW_NO_API ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwCreateContextEGL (TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _glfwInitEGL () ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  createShellSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  createSurface (TYPE_3__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    if (!createSurface(window, wndconfig))
        return GLFW_FALSE;

    if (ctxconfig->client != GLFW_NO_API)
    {
        if (!_glfwInitEGL())
            return GLFW_FALSE;
        if (!_glfwCreateContextEGL(window, ctxconfig, fbconfig))
            return GLFW_FALSE;
    }

    if (wndconfig->title)
        window->wl.title = strdup(wndconfig->title);

    if (wndconfig->visible)
    {
        if (!createShellSurface(window))
            return GLFW_FALSE;

        window->wl.visible = GLFW_TRUE;
    }
    else
    {
        window->wl.shell_surface = NULL;
        window->wl.visible = GLFW_FALSE;
    }

    window->wl.currentCursor = NULL;

    window->wl.monitors = calloc(1, sizeof(_GLFWmonitor*));
    window->wl.monitorsCount = 0;
    window->wl.monitorsSize = 1;

    return GLFW_TRUE;
}