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

/* Variables and functions */
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  printf (char*,double,int,int) ; 

__attribute__((used)) static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    printf("%0.2f Framebuffer resized to %ix%i\n", glfwGetTime(), width, height);

    glViewport(0, 0, width, height);
}