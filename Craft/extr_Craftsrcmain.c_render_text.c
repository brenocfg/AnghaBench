#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int /*<<< orphan*/  extra1; int /*<<< orphan*/  sampler; int /*<<< orphan*/  matrix; int /*<<< orphan*/  program; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* g ; 
 int /*<<< orphan*/  gen_text_buffer (float,float,float,char*) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_matrix_2d (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

void render_text(
    Attrib *attrib, int justify, float x, float y, float n, char *text)
{
    float matrix[16];
    set_matrix_2d(matrix, g->width, g->height);
    glUseProgram(attrib->program);
    glUniformMatrix4fv(attrib->matrix, 1, GL_FALSE, matrix);
    glUniform1i(attrib->sampler, 1);
    glUniform1i(attrib->extra1, 0);
    int length = strlen(text);
    x -= n * justify * (length - 1) / 2;
    GLuint buffer = gen_text_buffer(x, y, n, text);
    draw_text(attrib, buffer, length);
    del_buffer(buffer);
}