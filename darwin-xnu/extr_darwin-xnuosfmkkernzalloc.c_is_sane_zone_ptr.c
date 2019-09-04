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
typedef  TYPE_1__* zone_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  allows_foreign; scalar_t__ collectable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  pmap_kernel_va (int) ; 
 int zone_map_max_address ; 
 int zone_map_min_address ; 

__attribute__((used)) static inline boolean_t
is_sane_zone_ptr(zone_t		zone,
                 vm_offset_t	addr,
		 size_t		obj_size)
{
	/*  Must be aligned to pointer boundary */
	if (__improbable((addr & (sizeof(vm_offset_t) - 1)) != 0))
		return FALSE;

	/*  Must be a kernel address */
	if (__improbable(!pmap_kernel_va(addr)))
		return FALSE;

	/*  Must be from zone map if the zone only uses memory from the zone_map */
	/*
	 *  TODO: Remove the zone->collectable check when every
	 *  zone using foreign memory is properly tagged with allows_foreign
	 */
	if (zone->collectable && !zone->allows_foreign) {
		/*  check if addr is from zone map */
		if (addr                 >= zone_map_min_address &&
		   (addr + obj_size - 1) <  zone_map_max_address )
			return TRUE;

		return FALSE;
	}

	return TRUE;
}