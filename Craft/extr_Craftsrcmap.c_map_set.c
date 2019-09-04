#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int mask; int size; TYPE_2__* data; scalar_t__ dz; scalar_t__ dy; scalar_t__ dx; } ;
struct TYPE_7__ {int x; int y; int z; int w; } ;
struct TYPE_8__ {TYPE_1__ e; } ;
typedef  TYPE_2__ MapEntry ;
typedef  TYPE_3__ Map ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_ENTRY (TYPE_2__*) ; 
 unsigned int hash (int,int,int) ; 
 int /*<<< orphan*/  map_grow (TYPE_3__*) ; 

int map_set(Map *map, int x, int y, int z, int w) {
    unsigned int index = hash(x, y, z) & map->mask;
    x -= map->dx;
    y -= map->dy;
    z -= map->dz;
    MapEntry *entry = map->data + index;
    int overwrite = 0;
    while (!EMPTY_ENTRY(entry)) {
        if (entry->e.x == x && entry->e.y == y && entry->e.z == z) {
            overwrite = 1;
            break;
        }
        index = (index + 1) & map->mask;
        entry = map->data + index;
    }
    if (overwrite) {
        if (entry->e.w != w) {
            entry->e.w = w;
            return 1;
        }
    }
    else if (w) {
        entry->e.x = x;
        entry->e.y = y;
        entry->e.z = z;
        entry->e.w = w;
        map->size++;
        if (map->size * 2 > map->mask) {
            map_grow(map);
        }
        return 1;
    }
    return 0;
}