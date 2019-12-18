#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  instance; } ;
struct TYPE_5__ {TYPE_1__ opengl32; } ;
struct TYPE_6__ {TYPE_2__ wgl; } ;
typedef  scalar_t__ const GLFWglproc ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfw_wglGetProcAddress (char const*) ; 

GLFWglproc _glfwPlatformGetProcAddress(const char* procname)
{
    const GLFWglproc proc = (GLFWglproc) _glfw_wglGetProcAddress(procname);
    if (proc)
        return proc;

    return (GLFWglproc) GetProcAddress(_glfw.wgl.opengl32.instance, procname);
}