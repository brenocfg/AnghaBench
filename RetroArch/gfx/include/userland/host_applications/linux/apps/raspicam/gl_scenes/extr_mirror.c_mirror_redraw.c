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
struct TYPE_5__ {int /*<<< orphan*/ * attribute_locations; int /*<<< orphan*/ * uniform_locations; int /*<<< orphan*/  program; } ;
struct TYPE_4__ {int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ RASPITEX_STATE ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 TYPE_2__ mirror_shader ; 

__attribute__((used)) static int mirror_redraw(RASPITEX_STATE *raspitex_state) {
    static float offset = 0.0;

    // Start with a clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind the OES texture which is used to render the camera preview
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->texture);

    offset += 0.05;
    GLCHK(glUseProgram(mirror_shader.program));
    GLCHK(glEnableVertexAttribArray(mirror_shader.attribute_locations[0]));
    GLfloat varray[] = {
        -1.0f, -1.0f,
        1.0f,  1.0f,
        1.0f, -1.0f,

        -1.0f,  1.0f,
        1.0f,  1.0f,
        -1.0f, -1.0f,
    };
    GLCHK(glVertexAttribPointer(mirror_shader.attribute_locations[0], 2, GL_FLOAT, GL_FALSE, 0, varray));
    GLCHK(glUniform1f(mirror_shader.uniform_locations[1], offset));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    GLCHK(glDisableVertexAttribArray(mirror_shader.attribute_locations[0]));
    GLCHK(glUseProgram(0));
    return 0;
}