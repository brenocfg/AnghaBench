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
#define  GLFW_KEY_ESCAPE 129 
#define  GLFW_KEY_SPACE 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GL_TRUE ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwIconifyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double,char*) ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printf("%0.2f Key %s\n",
           glfwGetTime(),
           action == GLFW_PRESS ? "pressed" : "released");

    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_SPACE:
            glfwIconifyWindow(window);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
    }
}