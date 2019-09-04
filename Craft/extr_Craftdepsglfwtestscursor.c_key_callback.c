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
 int /*<<< orphan*/  GLFW_CURSOR ; 
 int /*<<< orphan*/  GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_CURSOR_HIDDEN ; 
 int /*<<< orphan*/  GLFW_CURSOR_NORMAL ; 
#define  GLFW_KEY_0 142 
#define  GLFW_KEY_1 141 
#define  GLFW_KEY_2 140 
#define  GLFW_KEY_3 139 
#define  GLFW_KEY_4 138 
#define  GLFW_KEY_5 137 
#define  GLFW_KEY_6 136 
#define  GLFW_KEY_A 135 
#define  GLFW_KEY_D 134 
#define  GLFW_KEY_ESCAPE 133 
#define  GLFW_KEY_H 132 
#define  GLFW_KEY_N 131 
#define  GLFW_KEY_SPACE 130 
#define  GLFW_KEY_T 129 
#define  GLFW_KEY_W 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int animate_cursor ; 
 int /*<<< orphan*/  glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ ** standard_cursors ; 
 int swap_interval ; 
 int track_cursor ; 
 int wait_events ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_A:
        {
            animate_cursor = !animate_cursor;
            if (!animate_cursor)
                glfwSetCursor(window, NULL);

            break;
        }

        case GLFW_KEY_ESCAPE:
        {
            if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
            {
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            }

            /* FALLTHROUGH */
        }

        case GLFW_KEY_N:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            printf("(( cursor is normal ))\n");
            break;

        case GLFW_KEY_D:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            printf("(( cursor is disabled ))\n");
            break;

        case GLFW_KEY_H:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            printf("(( cursor is hidden ))\n");
            break;

        case GLFW_KEY_SPACE:
            swap_interval = 1 - swap_interval;
            printf("(( swap interval: %i ))\n", swap_interval);
            glfwSwapInterval(swap_interval);
            break;

        case GLFW_KEY_W:
            wait_events = !wait_events;
            printf("(( %sing for events ))\n", wait_events ? "wait" : "poll");
            break;

        case GLFW_KEY_T:
            track_cursor = !track_cursor;
            break;

        case GLFW_KEY_0:
            glfwSetCursor(window, NULL);
            break;

        case GLFW_KEY_1:
            glfwSetCursor(window, standard_cursors[0]);
            break;

        case GLFW_KEY_2:
            glfwSetCursor(window, standard_cursors[1]);
            break;

        case GLFW_KEY_3:
            glfwSetCursor(window, standard_cursors[2]);
            break;

        case GLFW_KEY_4:
            glfwSetCursor(window, standard_cursors[3]);
            break;

        case GLFW_KEY_5:
            glfwSetCursor(window, standard_cursors[4]);
            break;

        case GLFW_KEY_6:
            glfwSetCursor(window, standard_cursors[5]);
            break;
    }
}