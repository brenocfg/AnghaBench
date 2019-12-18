#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int chunk_count; scalar_t__ sign_radius; TYPE_3__* chunks; int /*<<< orphan*/  render_radius; int /*<<< orphan*/  ortho; int /*<<< orphan*/  fov; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int /*<<< orphan*/  extra1; int /*<<< orphan*/  sampler; int /*<<< orphan*/  matrix; int /*<<< orphan*/  program; } ;
struct TYPE_13__ {int /*<<< orphan*/  maxy; int /*<<< orphan*/  miny; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_11__ {int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_1__ state; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Player ;
typedef  TYPE_3__ Chunk ;
typedef  TYPE_4__ Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ chunk_distance (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  chunk_visible (float**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chunked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_signs (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  frustum_planes (float**,int /*<<< orphan*/ ,float*) ; 
 TYPE_7__* g ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_matrix_3d (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void render_signs(Attrib *attrib, Player *player) {
    State *s = &player->state;
    int p = chunked(s->x);
    int q = chunked(s->z);
    float matrix[16];
    set_matrix_3d(
        matrix, g->width, g->height,
        s->x, s->y, s->z, s->rx, s->ry, g->fov, g->ortho, g->render_radius);
    float planes[6][4];
    frustum_planes(planes, g->render_radius, matrix);
    glUseProgram(attrib->program);
    glUniformMatrix4fv(attrib->matrix, 1, GL_FALSE, matrix);
    glUniform1i(attrib->sampler, 3);
    glUniform1i(attrib->extra1, 1);
    for (int i = 0; i < g->chunk_count; i++) {
        Chunk *chunk = g->chunks + i;
        if (chunk_distance(chunk, p, q) > g->sign_radius) {
            continue;
        }
        if (!chunk_visible(
            planes, chunk->p, chunk->q, chunk->miny, chunk->maxy))
        {
            continue;
        }
        draw_signs(attrib, chunk);
    }
}