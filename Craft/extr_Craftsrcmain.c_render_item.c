#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t item_index; int /*<<< orphan*/  scale; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  sampler; int /*<<< orphan*/  camera; int /*<<< orphan*/  matrix; int /*<<< orphan*/  program; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_cube (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_plant (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g ; 
 int /*<<< orphan*/  gen_cube_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  gen_plant_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 scalar_t__ is_plant (int) ; 
 int* items ; 
 int /*<<< orphan*/  set_matrix_item (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_of_day () ; 

void render_item(Attrib *attrib) {
    float matrix[16];
    set_matrix_item(matrix, g->width, g->height, g->scale);
    glUseProgram(attrib->program);
    glUniformMatrix4fv(attrib->matrix, 1, GL_FALSE, matrix);
    glUniform3f(attrib->camera, 0, 0, 5);
    glUniform1i(attrib->sampler, 0);
    glUniform1f(attrib->timer, time_of_day());
    int w = items[g->item_index];
    if (is_plant(w)) {
        GLuint buffer = gen_plant_buffer(0, 0, 0, 0.5, w);
        draw_plant(attrib, buffer);
        del_buffer(buffer);
    }
    else {
        GLuint buffer = gen_cube_buffer(0, 0, 0, 0.5, w);
        draw_cube(attrib, buffer);
        del_buffer(buffer);
    }
}