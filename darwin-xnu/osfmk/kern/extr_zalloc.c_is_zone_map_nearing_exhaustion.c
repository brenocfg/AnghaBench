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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int vm_map_max (TYPE_1__*) ; 
 int vm_map_min (TYPE_1__*) ; 
 TYPE_1__* zone_map ; 
 int zone_map_jetsam_limit ; 

boolean_t is_zone_map_nearing_exhaustion(void)
{
	uint64_t size = zone_map->size;
	uint64_t capacity = vm_map_max(zone_map) - vm_map_min(zone_map);
	if (size > ((capacity * zone_map_jetsam_limit) / 100)) {
		return TRUE;
	}
	return FALSE;
}