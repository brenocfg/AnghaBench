#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  surface; } ;
struct TYPE_8__ {TYPE_2__ egl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_1__ egl; } ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfw_eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwPlatformSwapBuffers(_GLFWwindow* window)
{
    _glfw_eglSwapBuffers(_glfw.egl.display, window->egl.surface);
}