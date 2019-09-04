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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 double gamma_value ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/ * glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetGamma (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

__attribute__((used)) static void set_gamma(GLFWwindow* window, float value)
{
    GLFWmonitor* monitor = glfwGetWindowMonitor(window);
    if (!monitor)
        monitor = glfwGetPrimaryMonitor();

    gamma_value = value;
    printf("Gamma: %f\n", gamma_value);
    glfwSetGamma(monitor, gamma_value);
}