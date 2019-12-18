#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_shell_surface {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwInputFramebufferSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowDamage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwInputWindowSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handleConfigure(void* data,
                            struct wl_shell_surface* shellSurface,
                            uint32_t edges,
                            int32_t width,
                            int32_t height)
{
    _GLFWwindow* window = data;
    _glfwInputFramebufferSize(window, width, height);
    _glfwInputWindowSize(window, width, height);
    _glfwPlatformSetWindowSize(window, width, height);
    _glfwInputWindowDamage(window);
}