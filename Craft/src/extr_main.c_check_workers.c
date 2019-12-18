#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ *** light_maps; int /*<<< orphan*/ *** block_maps; int /*<<< orphan*/  q; int /*<<< orphan*/  p; scalar_t__ load; } ;
typedef  TYPE_1__ WorkerItem ;
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  mtx; TYPE_1__ item; } ;
typedef  TYPE_2__ Worker ;
struct TYPE_11__ {TYPE_2__* workers; } ;
struct TYPE_10__ {int /*<<< orphan*/  lights; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  Map ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int WORKERS ; 
 scalar_t__ WORKER_DONE ; 
 scalar_t__ WORKER_IDLE ; 
 TYPE_3__* find_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_6__* g ; 
 int /*<<< orphan*/  generate_chunk (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  map_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void check_workers() {
    for (int i = 0; i < WORKERS; i++) {
        Worker *worker = g->workers + i;
        mtx_lock(&worker->mtx);
        if (worker->state == WORKER_DONE) {
            WorkerItem *item = &worker->item;
            Chunk *chunk = find_chunk(item->p, item->q);
            if (chunk) {
                if (item->load) {
                    Map *block_map = item->block_maps[1][1];
                    Map *light_map = item->light_maps[1][1];
                    map_free(&chunk->map);
                    map_free(&chunk->lights);
                    map_copy(&chunk->map, block_map);
                    map_copy(&chunk->lights, light_map);
                    request_chunk(item->p, item->q);
                }
                generate_chunk(chunk, item);
            }
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    Map *block_map = item->block_maps[a][b];
                    Map *light_map = item->light_maps[a][b];
                    if (block_map) {
                        map_free(block_map);
                        free(block_map);
                    }
                    if (light_map) {
                        map_free(light_map);
                        free(light_map);
                    }
                }
            }
            worker->state = WORKER_IDLE;
        }
        mtx_unlock(&worker->mtx);
    }
}