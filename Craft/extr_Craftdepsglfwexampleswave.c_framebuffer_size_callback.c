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
typedef  scalar_t__ mat4x4 ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PROJECTION ; 
 scalar_t__ M_PI ; 
 int /*<<< orphan*/  glLoadMatrixf (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mat4x4_perspective (scalar_t__,float,float,float,float) ; 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    float ratio = 1.f;
    mat4x4 projection;

    if (height > 0)
        ratio = (float) width / (float) height;

    // Setup viewport
    glViewport(0, 0, width, height);

    // Change to the projection matrix and set our viewing volume
    glMatrixMode(GL_PROJECTION);
    mat4x4_perspective(projection,
                       60.f * (float) M_PI / 180.f,
                       ratio,
                       1.f, 1024.f);
    glLoadMatrixf((const GLfloat*) projection);
}