#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_shell_surface {int dummy; } ;
typedef  float int32_t ;
struct TYPE_5__ {scalar_t__ numer; scalar_t__ denom; scalar_t__ minwidth; scalar_t__ maxwidth; scalar_t__ minheight; scalar_t__ maxheight; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_1__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLFW_DONT_CARE ; 
 int /*<<< orphan*/  _glfwInputWindowDamage (TYPE_1__*) ; 
 int /*<<< orphan*/  _glfwInputWindowSize (TYPE_1__*,float,float) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowSize (TYPE_1__*,float,float) ; 

__attribute__((used)) static void handleConfigure(void* data,
                            struct wl_shell_surface* shellSurface,
                            uint32_t edges,
                            int32_t width,
                            int32_t height)
{
    _GLFWwindow* window = data;
    float aspectRatio;
    float targetRatio;

    if (!window->monitor)
    {
        if (window->numer != GLFW_DONT_CARE && window->denom != GLFW_DONT_CARE)
        {
            aspectRatio = (float)width / (float)height;
            targetRatio = (float)window->numer / (float)window->denom;
            if (aspectRatio < targetRatio)
                height = width / targetRatio;
            else if (aspectRatio > targetRatio)
                width = height * targetRatio;
        }

        if (window->minwidth != GLFW_DONT_CARE && width < window->minwidth)
            width = window->minwidth;
        else if (window->maxwidth != GLFW_DONT_CARE && width > window->maxwidth)
            width = window->maxwidth;

        if (window->minheight != GLFW_DONT_CARE && height < window->minheight)
            height = window->minheight;
        else if (window->maxheight != GLFW_DONT_CARE && height > window->maxheight)
            height = window->maxheight;
    }

    _glfwInputWindowSize(window, width, height);
    _glfwPlatformSetWindowSize(window, width, height);
    _glfwInputWindowDamage(window);
}