#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * dc; } ;
struct TYPE_6__ {TYPE_1__ wgl; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwSetContextTLS (TYPE_2__*) ; 
 int /*<<< orphan*/  _glfw_wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void _glfwPlatformMakeContextCurrent(_GLFWwindow* window)
{
    if (window)
        _glfw_wglMakeCurrent(window->wgl.dc, window->wgl.context);
    else
        _glfw_wglMakeCurrent(NULL, NULL);

    _glfwSetContextTLS(window);
}