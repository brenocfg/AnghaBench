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
 int /*<<< orphan*/  Draw () ; 
 int /*<<< orphan*/  GLFW_KEY_LEFT ; 
 int /*<<< orphan*/  GLFW_KEY_RIGHT ; 
 scalar_t__ GLFW_PRESS ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  glClear (int) ; 
 scalar_t__ glfwGetKey (int /*<<< orphan*/ ) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwSwapBuffers () ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 double old_time ; 
 double rotate_y ; 
 double rotate_z ; 
 double rotations_per_tick ; 

void Iteration()
{
    // calculate time elapsed, and the amount by which stuff rotates
    double current_time = glfwGetTime(),
          delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
    old_time = current_time;
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
      rotate_y += delta_rotate;
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
      rotate_y -= delta_rotate;
    // z axis always rotates
    rotate_z += delta_rotate;
 
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw the figure
    Draw();

    // Test that glfwSwapInterval doesn't crash (although we don't test actual timings)
    static int i = 0;
    glfwSwapInterval(i);
    if (i < 2) ++i;

    // swap back and front buffers
    glfwSwapBuffers();
}