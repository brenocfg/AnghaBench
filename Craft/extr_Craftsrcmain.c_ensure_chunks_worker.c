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
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int p; int q; int load; int /*<<< orphan*/ *** light_maps; int /*<<< orphan*/ *** block_maps; } ;
typedef  TYPE_1__ WorkerItem ;
struct TYPE_12__ {int index; int /*<<< orphan*/  cnd; int /*<<< orphan*/  state; TYPE_1__ item; } ;
typedef  TYPE_2__ Worker ;
struct TYPE_16__ {int create_radius; scalar_t__ chunk_count; TYPE_5__* chunks; int /*<<< orphan*/  render_radius; int /*<<< orphan*/  ortho; int /*<<< orphan*/  fov; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int p; int q; scalar_t__ dirty; int /*<<< orphan*/  lights; int /*<<< orphan*/  map; scalar_t__ buffer; } ;
struct TYPE_13__ {int /*<<< orphan*/  z; int /*<<< orphan*/  x; int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; int /*<<< orphan*/  y; } ;
struct TYPE_14__ {TYPE_3__ state; } ;
typedef  TYPE_3__ State ;
typedef  TYPE_4__ Player ;
typedef  int /*<<< orphan*/  Map ;
typedef  TYPE_5__ Chunk ;

/* Variables and functions */
 int ABS (int) ; 
 int MAX (int,int) ; 
 scalar_t__ MAX_CHUNKS ; 
 int WORKERS ; 
 int /*<<< orphan*/  WORKER_BUSY ; 
 int /*<<< orphan*/  chunk_visible (float**,int,int,int /*<<< orphan*/ ,int) ; 
 int chunked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnd_signal (int /*<<< orphan*/ *) ; 
 TYPE_5__* find_chunk (int,int) ; 
 int /*<<< orphan*/  frustum_planes (float**,int /*<<< orphan*/ ,float*) ; 
 TYPE_7__* g ; 
 int /*<<< orphan*/  init_chunk (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  map_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_matrix_3d (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ensure_chunks_worker(Player *player, Worker *worker) {
    State *s = &player->state;
    float matrix[16];
    set_matrix_3d(
        matrix, g->width, g->height,
        s->x, s->y, s->z, s->rx, s->ry, g->fov, g->ortho, g->render_radius);
    float planes[6][4];
    frustum_planes(planes, g->render_radius, matrix);
    int p = chunked(s->x);
    int q = chunked(s->z);
    int r = g->create_radius;
    int start = 0x0fffffff;
    int best_score = start;
    int best_a = 0;
    int best_b = 0;
    for (int dp = -r; dp <= r; dp++) {
        for (int dq = -r; dq <= r; dq++) {
            int a = p + dp;
            int b = q + dq;
            int index = (ABS(a) ^ ABS(b)) % WORKERS;
            if (index != worker->index) {
                continue;
            }
            Chunk *chunk = find_chunk(a, b);
            if (chunk && !chunk->dirty) {
                continue;
            }
            int distance = MAX(ABS(dp), ABS(dq));
            int invisible = !chunk_visible(planes, a, b, 0, 256);
            int priority = 0;
            if (chunk) {
                priority = chunk->buffer && chunk->dirty;
            }
            int score = (invisible << 24) | (priority << 16) | distance;
            if (score < best_score) {
                best_score = score;
                best_a = a;
                best_b = b;
            }
        }
    }
    if (best_score == start) {
        return;
    }
    int a = best_a;
    int b = best_b;
    int load = 0;
    Chunk *chunk = find_chunk(a, b);
    if (!chunk) {
        load = 1;
        if (g->chunk_count < MAX_CHUNKS) {
            chunk = g->chunks + g->chunk_count++;
            init_chunk(chunk, a, b);
        }
        else {
            return;
        }
    }
    WorkerItem *item = &worker->item;
    item->p = chunk->p;
    item->q = chunk->q;
    item->load = load;
    for (int dp = -1; dp <= 1; dp++) {
        for (int dq = -1; dq <= 1; dq++) {
            Chunk *other = chunk;
            if (dp || dq) {
                other = find_chunk(chunk->p + dp, chunk->q + dq);
            }
            if (other) {
                Map *block_map = malloc(sizeof(Map));
                map_copy(block_map, &other->map);
                Map *light_map = malloc(sizeof(Map));
                map_copy(light_map, &other->lights);
                item->block_maps[dp + 1][dq + 1] = block_map;
                item->light_maps[dp + 1][dq + 1] = light_map;
            }
            else {
                item->block_maps[dp + 1][dq + 1] = 0;
                item->light_maps[dp + 1][dq + 1] = 0;
            }
        }
    }
    chunk->dirty = 0;
    worker->state = WORKER_BUSY;
    cnd_signal(&worker->cnd);
}