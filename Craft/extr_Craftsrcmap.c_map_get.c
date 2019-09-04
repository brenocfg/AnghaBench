#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int mask; TYPE_2__* data; scalar_t__ dz; scalar_t__ dy; scalar_t__ dx; } ;
struct TYPE_6__ {int x; int y; int z; int w; } ;
struct TYPE_7__ {TYPE_1__ e; } ;
typedef  TYPE_2__ MapEntry ;
typedef  TYPE_3__ Map ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_ENTRY (TYPE_2__*) ; 
 unsigned int hash (int,int,int) ; 

int map_get(Map *map, int x, int y, int z) {
    unsigned int index = hash(x, y, z) & map->mask;
    x -= map->dx;
    y -= map->dy;
    z -= map->dz;
    if (x < 0 || x > 255) return 0;
    if (y < 0 || y > 255) return 0;
    if (z < 0 || z > 255) return 0;
    MapEntry *entry = map->data + index;
    while (!EMPTY_ENTRY(entry)) {
        if (entry->e.x == x && entry->e.y == y && entry->e.z == z) {
            return entry->e.w;
        }
        index = (index + 1) & map->mask;
        entry = map->data + index;
    }
    return 0;
}