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
struct TYPE_4__ {scalar_t__ client; } ;
struct TYPE_5__ {TYPE_1__ egl; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  scalar_t__ GLFWglproc ;

/* Variables and functions */
 TYPE_2__* _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/  _glfw_dlsym (scalar_t__,char const*) ; 
 scalar_t__ _glfw_eglGetProcAddress (char const*) ; 

GLFWglproc _glfwPlatformGetProcAddress(const char* procname)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    if (window->egl.client)
    {
        GLFWglproc proc = (GLFWglproc) _glfw_dlsym(window->egl.client, procname);
        if (proc)
            return proc;
    }

    return _glfw_eglGetProcAddress(procname);
}