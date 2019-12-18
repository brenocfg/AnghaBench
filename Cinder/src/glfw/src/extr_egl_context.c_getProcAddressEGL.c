#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ client; } ;
struct TYPE_6__ {TYPE_1__ egl; } ;
struct TYPE_7__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  scalar_t__ GLFWglproc ;

/* Variables and functions */
 TYPE_3__* _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/  _glfw_dlsym (scalar_t__,char const*) ; 
 scalar_t__ eglGetProcAddress (char const*) ; 

__attribute__((used)) static GLFWglproc getProcAddressEGL(const char* procname)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    if (window->context.egl.client)
    {
        GLFWglproc proc = (GLFWglproc) _glfw_dlsym(window->context.egl.client,
                                                   procname);
        if (proc)
            return proc;
    }

    return eglGetProcAddress(procname);
}