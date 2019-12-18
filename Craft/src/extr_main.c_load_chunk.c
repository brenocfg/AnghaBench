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
struct TYPE_3__ {int p; int q; int /*<<< orphan*/ *** light_maps; int /*<<< orphan*/ *** block_maps; } ;
typedef  TYPE_1__ WorkerItem ;
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/  create_world (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_load_blocks (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  db_load_lights (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  map_set_func ; 

void load_chunk(WorkerItem *item) {
    int p = item->p;
    int q = item->q;
    Map *block_map = item->block_maps[1][1];
    Map *light_map = item->light_maps[1][1];
    create_world(p, q, map_set_func, block_map);
    db_load_blocks(block_map, p, q);
    db_load_lights(light_map, p, q);
}