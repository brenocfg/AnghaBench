#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int ortho; float render_radius; int chunk_count; TYPE_3__* chunks; int /*<<< orphan*/  fov; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  extra4; int /*<<< orphan*/  extra3; int /*<<< orphan*/  extra2; int /*<<< orphan*/  extra1; int /*<<< orphan*/  sampler; int /*<<< orphan*/  camera; int /*<<< orphan*/  matrix; int /*<<< orphan*/  program; } ;
struct TYPE_14__ {scalar_t__ faces; int /*<<< orphan*/  maxy; int /*<<< orphan*/  miny; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_12__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; } ;
struct TYPE_13__ {TYPE_1__ state; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Player ;
typedef  TYPE_3__ Chunk ;
typedef  TYPE_4__ Attrib ;

/* Variables and functions */
 float CHUNK_SIZE ; 
 int /*<<< orphan*/  GL_FALSE ; 
 float chunk_distance (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  chunk_visible (float**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chunked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_chunk (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ensure_chunks (TYPE_2__*) ; 
 int /*<<< orphan*/  frustum_planes (float**,float,float*) ; 
 TYPE_7__* g ; 
 float get_daylight () ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniform3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_matrix_3d (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float) ; 
 float time_of_day () ; 

int render_chunks(Attrib *attrib, Player *player) {
    int result = 0;
    State *s = &player->state;
    ensure_chunks(player);
    int p = chunked(s->x);
    int q = chunked(s->z);
    float light = get_daylight();
    float matrix[16];
    set_matrix_3d(
        matrix, g->width, g->height,
        s->x, s->y, s->z, s->rx, s->ry, g->fov, g->ortho, g->render_radius);
    float planes[6][4];
    frustum_planes(planes, g->render_radius, matrix);
    glUseProgram(attrib->program);
    glUniformMatrix4fv(attrib->matrix, 1, GL_FALSE, matrix);
    glUniform3f(attrib->camera, s->x, s->y, s->z);
    glUniform1i(attrib->sampler, 0);
    glUniform1i(attrib->extra1, 2);
    glUniform1f(attrib->extra2, light);
    glUniform1f(attrib->extra3, g->render_radius * CHUNK_SIZE);
    glUniform1i(attrib->extra4, g->ortho);
    glUniform1f(attrib->timer, time_of_day());
    for (int i = 0; i < g->chunk_count; i++) {
        Chunk *chunk = g->chunks + i;
        if (chunk_distance(chunk, p, q) > g->render_radius) {
            continue;
        }
        if (!chunk_visible(
            planes, chunk->p, chunk->q, chunk->miny, chunk->maxy))
        {
            continue;
        }
        draw_chunk(attrib, chunk);
        result += chunk->faces;
    }
    return result;
}