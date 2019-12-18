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
struct TYPE_4__ {struct TYPE_4__* bands; struct TYPE_4__* block_bitmap; } ;
typedef  TYPE_1__ shadow_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  my_free (TYPE_1__*) ; 

void
shadow_map_free(shadow_map_t * map)
{	
    if (map->block_bitmap)
	my_free(map->block_bitmap);
    if (map->bands)
	my_free(map->bands);
    map->block_bitmap = NULL;
    map->bands = NULL;
    my_free(map);
    return;
}