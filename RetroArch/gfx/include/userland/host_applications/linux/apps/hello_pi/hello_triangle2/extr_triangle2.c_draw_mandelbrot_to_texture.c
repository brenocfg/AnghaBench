#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  unif_centre2; int /*<<< orphan*/  unif_scale2; int /*<<< orphan*/  program2; int /*<<< orphan*/  buf; int /*<<< orphan*/  tex_fb; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_1__ CUBE_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 int /*<<< orphan*/  check () ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glFinish () ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glUniform2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_mandelbrot_to_texture(CUBE_STATE_T *state, GLfloat cx, GLfloat cy, GLfloat scale)
{
        // Draw the mandelbrot to a texture
        glBindFramebuffer(GL_FRAMEBUFFER,state->tex_fb);
        check();
        glBindBuffer(GL_ARRAY_BUFFER, state->buf);

        glUseProgram ( state->program2 );
        check();

        glUniform2f(state->unif_scale2, scale, scale);
        glUniform2f(state->unif_centre2, cx, cy);
        check();
        glDrawArrays ( GL_TRIANGLE_FAN, 0, 4 );
        check();

        glFlush();
        glFinish();
        check();
}