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
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* glfwGetMonitorName (int /*<<< orphan*/ *) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowCloseCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  window_close_callback ; 

__attribute__((used)) static GLFWwindow* open_window(int width, int height, GLFWmonitor* monitor)
{
    double base;
    GLFWwindow* window;

    base = glfwGetTime();

    window = glfwCreateWindow(width, height, "Window Re-opener", monitor, NULL);
    if (!window)
        return NULL;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetKeyCallback(window, key_callback);

    if (monitor)
    {
        printf("Opening full screen window on monitor %s took %0.3f seconds\n",
               glfwGetMonitorName(monitor),
               glfwGetTime() - base);
    }
    else
    {
        printf("Opening regular window took %0.3f seconds\n",
               glfwGetTime() - base);
    }

    return window;
}