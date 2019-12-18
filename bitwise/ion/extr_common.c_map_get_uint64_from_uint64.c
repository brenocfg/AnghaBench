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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ len; int cap; scalar_t__* keys; scalar_t__* vals; } ;
typedef  TYPE_1__ Map ;

/* Variables and functions */
 int IS_POW2 (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hash_uint64 (scalar_t__) ; 

uint64_t map_get_uint64_from_uint64(Map *map, uint64_t key) {
    if (map->len == 0) {
        return 0;
    }
    assert(IS_POW2(map->cap));
    size_t i = (size_t)hash_uint64(key);
    assert(map->len < map->cap);
    for (;;) {
        i &= map->cap - 1;
        if (map->keys[i] == key) {
            return map->vals[i];
        } else if (!map->keys[i]) {
            return 0;
        }
        i++;
    }
    return 0;
}