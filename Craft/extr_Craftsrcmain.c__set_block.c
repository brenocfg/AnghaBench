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
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  Map ;
typedef  TYPE_1__ Chunk ;

/* Variables and functions */
 int chunked (int) ; 
 int /*<<< orphan*/  db_insert_block (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dirty_chunk (TYPE_1__*) ; 
 TYPE_1__* find_chunk (int,int) ; 
 scalar_t__ map_set (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  set_light (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unset_sign (int,int,int) ; 

void _set_block(int p, int q, int x, int y, int z, int w, int dirty) {
    Chunk *chunk = find_chunk(p, q);
    if (chunk) {
        Map *map = &chunk->map;
        if (map_set(map, x, y, z, w)) {
            if (dirty) {
                dirty_chunk(chunk);
            }
            db_insert_block(p, q, x, y, z, w);
        }
    }
    else {
        db_insert_block(p, q, x, y, z, w);
    }
    if (w == 0 && chunked(x) == p && chunked(z) == q) {
        unset_sign(x, y, z);
        set_light(p, q, x, y, z, 0);
    }
}