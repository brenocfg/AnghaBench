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

/* Variables and functions */
 int /*<<< orphan*/  GLFW_KEY_SPACE ; 
 scalar_t__ GLFW_PRESS ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 scalar_t__ glfwGetKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int last_state ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int step ; 
 int /*<<< orphan*/  window ; 

void render() {
    // http://www.glfw.org/docs/latest/input_guide.html#input_key
    int state = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    if (last_state != state) { // to not spam console
        last_state = state;
        printf("glfwGetKey says space pressed? %d\n", state);
        if (state && step == 1) {
            printf("%d. Switch out of your browser to another window (while holding space)\n", step++);
        }
        if (!state && step == 2) {
            printf("You let go, please press and hold spacebar\n");
            step = 1;
        }
    }

    // Red while space is pressed, green while not
    if (state) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);
}