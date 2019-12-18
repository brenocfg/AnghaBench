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
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int LIST_MODE ; 
 int TEST_MODE ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ ** glfwGetMonitors (int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  list_modes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_modes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char** argv)
{
    int ch, i, count, mode = LIST_MODE;
    GLFWmonitor** monitors;

    while ((ch = getopt(argc, argv, "th")) != -1)
    {
        switch (ch)
        {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 't':
                mode = TEST_MODE;
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    monitors = glfwGetMonitors(&count);

    for (i = 0;  i < count;  i++)
    {
        if (mode == LIST_MODE)
            list_modes(monitors[i]);
        else if (mode == TEST_MODE)
            test_modes(monitors[i]);
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}