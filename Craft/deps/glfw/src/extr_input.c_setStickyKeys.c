#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int stickyKeys; scalar_t__* keys; } ;
typedef  TYPE_1__ _GLFWwindow ;

/* Variables and functions */
 int GLFW_KEY_LAST ; 
 scalar_t__ GLFW_RELEASE ; 
 scalar_t__ _GLFW_STICK ; 

__attribute__((used)) static void setStickyKeys(_GLFWwindow* window, int enabled)
{
    if (window->stickyKeys == enabled)
        return;

    if (!enabled)
    {
        int i;

        // Release all sticky keys
        for (i = 0;  i <= GLFW_KEY_LAST;  i++)
        {
            if (window->keys[i] == _GLFW_STICK)
                window->keys[i] = GLFW_RELEASE;
        }
    }

    window->stickyKeys = enabled;
}