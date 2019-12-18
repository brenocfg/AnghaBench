#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ *** light_maps; int /*<<< orphan*/ *** block_maps; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ WorkerItem ;
struct TYPE_7__ {int /*<<< orphan*/  lights; int /*<<< orphan*/  map; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  init_chunk (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  load_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  request_chunk (int,int) ; 

void create_chunk(Chunk *chunk, int p, int q) {
    init_chunk(chunk, p, q);

    WorkerItem _item;
    WorkerItem *item = &_item;
    item->p = chunk->p;
    item->q = chunk->q;
    item->block_maps[1][1] = &chunk->map;
    item->light_maps[1][1] = &chunk->lights;
    load_chunk(item);

    request_chunk(p, q);
}