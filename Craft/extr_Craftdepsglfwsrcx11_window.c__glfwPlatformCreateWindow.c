#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ monitor; } ;
typedef  TYPE_1__ _GLFWwndconfig ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
typedef  int /*<<< orphan*/  _GLFWctxconfig ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  _glfwCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _glfwPlatformShowWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createWindow (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  enterFullscreenMode (int /*<<< orphan*/ *) ; 

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GL_FALSE;

    if (!createWindow(window, wndconfig))
        return GL_FALSE;

    if (wndconfig->monitor)
    {
        _glfwPlatformShowWindow(window);
        enterFullscreenMode(window);
    }

    return GL_TRUE;
}