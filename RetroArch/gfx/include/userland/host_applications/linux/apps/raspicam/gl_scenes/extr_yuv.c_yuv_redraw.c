#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * attribute_locations; int /*<<< orphan*/  program; } ;
struct TYPE_4__ {int /*<<< orphan*/  texture; int /*<<< orphan*/  v_texture; int /*<<< orphan*/  u_texture; int /*<<< orphan*/  y_texture; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttrib2f (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varray ; 
 TYPE_2__ yuv_shader ; 

__attribute__((used)) static int yuv_redraw(RASPITEX_STATE *raspitex_state)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLCHK(glUseProgram(yuv_shader.program));
    GLCHK(glActiveTexture(GL_TEXTURE0));
    GLCHK(glEnableVertexAttribArray(yuv_shader.attribute_locations[0]));
    GLCHK(glVertexAttribPointer(yuv_shader.attribute_locations[0],
             2, GL_FLOAT, GL_FALSE, 0, varray));

    // Y plane
    GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->y_texture));
    GLCHK(glVertexAttrib2f(yuv_shader.attribute_locations[1], -1.0f, 1.0f));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    // U plane
    GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->u_texture));
    GLCHK(glVertexAttrib2f(yuv_shader.attribute_locations[1], 0.0f, 1.0f));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    // V plane
    GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->v_texture));
    GLCHK(glVertexAttrib2f(yuv_shader.attribute_locations[1], 0.0f, 0.0f));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    // RGB plane
    GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->texture));
    GLCHK(glVertexAttrib2f(yuv_shader.attribute_locations[1], -1.0f, 0.0f));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    GLCHK(glDisableVertexAttribArray(yuv_shader.attribute_locations[0]));
    GLCHK(glUseProgram(0));
    return 0;
}