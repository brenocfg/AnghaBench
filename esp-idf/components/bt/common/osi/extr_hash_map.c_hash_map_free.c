#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* bucket; } ;
typedef  TYPE_1__ hash_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_map_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 

void hash_map_free(hash_map_t *hash_map)
{
    if (hash_map == NULL) {
        return;
    }
    hash_map_clear(hash_map);
    osi_free(hash_map->bucket);
    osi_free(hash_map);
}