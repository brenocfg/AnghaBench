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
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {TYPE_1__ videoMode; scalar_t__ monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowSize (TYPE_2__*,int,int) ; 

void glfwSetWindowSize(GLFWwindow* handle, int width, int height)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    _GLFW_REQUIRE_INIT();

    if (window->monitor)
    {
        window->videoMode.width  = width;
        window->videoMode.height = height;
    }

    _glfwPlatformSetWindowSize(window, width, height);
}