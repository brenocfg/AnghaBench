#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lights; } ;
typedef  int /*<<< orphan*/  Map ;
typedef  TYPE_1__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  db_insert_light (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dirty_chunk (TYPE_1__*) ; 
 TYPE_1__* find_chunk (int,int) ; 
 scalar_t__ map_set (int /*<<< orphan*/ *,int,int,int,int) ; 

void set_light(int p, int q, int x, int y, int z, int w) {
    Chunk *chunk = find_chunk(p, q);
    if (chunk) {
        Map *map = &chunk->lights;
        if (map_set(map, x, y, z, w)) {
            dirty_chunk(chunk);
            db_insert_light(p, q, x, y, z, w);
        }
    }
    else {
        db_insert_light(p, q, x, y, z, w);
    }
}