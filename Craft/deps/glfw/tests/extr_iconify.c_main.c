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
typedef  scalar_t__ GLboolean ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_AUTO_ICONIFY ; 
 int /*<<< orphan*/  GLFW_FOCUSED ; 
 int /*<<< orphan*/  GLFW_ICONIFIED ; 
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/ * create_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ ** glfwGetMonitors (int*) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 scalar_t__ glfwGetWindowAttrib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowFocusCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowIconifyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  glfwSetWindowSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  window_focus_callback ; 
 int /*<<< orphan*/  window_iconify_callback ; 
 int /*<<< orphan*/  window_refresh_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_size_callback ; 

int main(int argc, char** argv)
{
    int ch, i, window_count;
    GLboolean auto_iconify = GL_TRUE, fullscreen = GL_FALSE, all_monitors = GL_FALSE;
    GLFWwindow** windows;

    while ((ch = getopt(argc, argv, "afhn")) != -1)
    {
        switch (ch)
        {
            case 'a':
                all_monitors = GL_TRUE;
                break;

            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case 'f':
                fullscreen = GL_TRUE;
                break;

            case 'n':
                auto_iconify = GL_FALSE;
                break;

            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_AUTO_ICONIFY, auto_iconify);

    if (fullscreen && all_monitors)
    {
        int monitor_count;
        GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

        window_count = monitor_count;
        windows = calloc(window_count, sizeof(GLFWwindow*));

        for (i = 0;  i < monitor_count;  i++)
        {
            windows[i] = create_window(monitors[i]);
            if (!windows[i])
                break;
        }
    }
    else
    {
        GLFWmonitor* monitor = NULL;

        if (fullscreen)
            monitor = glfwGetPrimaryMonitor();

        window_count = 1;
        windows = calloc(window_count, sizeof(GLFWwindow*));
        windows[0] = create_window(monitor);
    }

    for (i = 0;  i < window_count;  i++)
    {
        glfwSetKeyCallback(windows[i], key_callback);
        glfwSetFramebufferSizeCallback(windows[i], framebuffer_size_callback);
        glfwSetWindowSizeCallback(windows[i], window_size_callback);
        glfwSetWindowFocusCallback(windows[i], window_focus_callback);
        glfwSetWindowIconifyCallback(windows[i], window_iconify_callback);
        glfwSetWindowRefreshCallback(windows[i], window_refresh_callback);

        window_refresh_callback(windows[i]);

        printf("Window is %s and %s\n",
            glfwGetWindowAttrib(windows[i], GLFW_ICONIFIED) ? "iconified" : "restored",
            glfwGetWindowAttrib(windows[i], GLFW_FOCUSED) ? "focused" : "defocused");
    }

    for (;;)
    {
        glfwPollEvents();

        for (i = 0;  i < window_count;  i++)
        {
            if (glfwWindowShouldClose(windows[i]))
                break;
        }

        if (i < window_count)
            break;

        // Workaround for an issue with msvcrt and mintty
        fflush(stdout);
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}