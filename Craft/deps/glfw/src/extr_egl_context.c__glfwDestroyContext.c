#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ context; scalar_t__ surface; int /*<<< orphan*/ * visual; int /*<<< orphan*/ * client; } ;
struct TYPE_7__ {scalar_t__ api; } ;
struct TYPE_10__ {TYPE_3__ egl; TYPE_1__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;
struct TYPE_11__ {TYPE_2__ egl; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfw_dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfw_eglDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _glfw_eglDestroySurface (int /*<<< orphan*/ ,scalar_t__) ; 

void _glfwDestroyContext(_GLFWwindow* window)
{
#if defined(_GLFW_X11)
    // NOTE: Do not unload libGL.so.1 while the X11 display is still open,
    //       as it will make XCloseDisplay segfault
    if (window->context.api != GLFW_OPENGL_API)
#endif // _GLFW_X11
    {
        if (window->egl.client)
        {
            _glfw_dlclose(window->egl.client);
            window->egl.client = NULL;
        }
    }

#if defined(_GLFW_X11)
    if (window->egl.visual)
    {
       XFree(window->egl.visual);
       window->egl.visual = NULL;
    }
#endif // _GLFW_X11

    if (window->egl.surface)
    {
        _glfw_eglDestroySurface(_glfw.egl.display, window->egl.surface);
        window->egl.surface = EGL_NO_SURFACE;
    }

    if (window->egl.context)
    {
        _glfw_eglDestroyContext(_glfw.egl.display, window->egl.context);
        window->egl.context = EGL_NO_CONTEXT;
    }
}