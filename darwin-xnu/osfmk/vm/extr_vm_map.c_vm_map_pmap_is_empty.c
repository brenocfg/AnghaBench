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
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*,TYPE_1__*,long long,long long,scalar_t__,long long) ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pmap_is_empty (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

boolean_t vm_map_pmap_is_empty(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end)
{
#ifdef MACHINE_PMAP_IS_EMPTY
	return pmap_is_empty(map->pmap, start, end);
#else 	/* MACHINE_PMAP_IS_EMPTY */
	vm_map_offset_t	offset;
	ppnum_t		phys_page;

	if (map->pmap == NULL) {
		return TRUE;
	}

	for (offset = start;
	     offset < end;
	     offset += PAGE_SIZE) {
		phys_page = pmap_find_phys(map->pmap, offset);
		if (phys_page) {
			kprintf("vm_map_pmap_is_empty(%p,0x%llx,0x%llx): "
				"page %d at 0x%llx\n",
				map, (long long)start, (long long)end,
				phys_page, (long long)offset);
			return FALSE;
		}
	}
	return TRUE;
#endif	/* MACHINE_PMAP_IS_EMPTY */
}