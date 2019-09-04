#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ surface; int /*<<< orphan*/  context; int /*<<< orphan*/  config; } ;
struct TYPE_9__ {TYPE_2__ egl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
struct TYPE_10__ {TYPE_1__ egl; } ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ _GLFW_EGL_NATIVE_WINDOW ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwSetContextTLS (TYPE_3__*) ; 
 scalar_t__ _glfw_eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfw_eglGetError () ; 
 int /*<<< orphan*/  _glfw_eglMakeCurrent (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getErrorString (int /*<<< orphan*/ ) ; 

void _glfwPlatformMakeContextCurrent(_GLFWwindow* window)
{
    if (window)
    {
        if (window->egl.surface == EGL_NO_SURFACE)
        {
            window->egl.surface =
                _glfw_eglCreateWindowSurface(_glfw.egl.display,
                                             window->egl.config,
                                             (EGLNativeWindowType)_GLFW_EGL_NATIVE_WINDOW,
                                             NULL);
            if (window->egl.surface == EGL_NO_SURFACE)
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "EGL: Failed to create window surface: %s",
                                getErrorString(_glfw_eglGetError()));
            }
        }

        _glfw_eglMakeCurrent(_glfw.egl.display,
                             window->egl.surface,
                             window->egl.surface,
                             window->egl.context);
    }
    else
    {
        _glfw_eglMakeCurrent(_glfw.egl.display,
                             EGL_NO_SURFACE,
                             EGL_NO_SURFACE,
                             EGL_NO_CONTEXT);
    }

    _glfwSetContextTLS(window);
}