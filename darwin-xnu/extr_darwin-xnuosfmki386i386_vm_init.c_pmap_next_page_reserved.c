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
typedef  size_t uint32_t ;
typedef  scalar_t__ ppnum_t ;
struct TYPE_3__ {scalar_t__ alloc_up; scalar_t__ alloc_down; } ;
typedef  TYPE_1__ pmap_memory_region_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  avail_remaining ; 
 scalar_t__ lowest_lo ; 
 scalar_t__ max_ppnum ; 
 size_t pmap_last_reserved_range_index ; 
 TYPE_1__* pmap_memory_regions ; 
 int /*<<< orphan*/  pmap_reserved_pages_allocated ; 
 size_t* pmap_reserved_range_indices ; 
 scalar_t__ pmap_reserved_ranges ; 

boolean_t
pmap_next_page_reserved(ppnum_t *pn) {
	if (pmap_reserved_ranges) {
		uint32_t n;
		pmap_memory_region_t *region;
		for (n = 0; n < pmap_last_reserved_range_index; n++) {
			uint32_t reserved_index = pmap_reserved_range_indices[n];
			region = &pmap_memory_regions[reserved_index];
			if (region->alloc_up <= region->alloc_down) {
				*pn = region->alloc_up++;
				avail_remaining--;

				if (*pn > max_ppnum)
					max_ppnum = *pn;

				if (lowest_lo == 0 || *pn < lowest_lo)
					lowest_lo = *pn;

				pmap_reserved_pages_allocated++;
#if DEBUG
				if (region->alloc_up > region->alloc_down) {
					kprintf("Exhausted reserved range index: %u, base: 0x%x end: 0x%x, type: 0x%x, attribute: 0x%llx\n", reserved_index, region->base, region->end, region->type, region->attribute);
				}
#endif
				return TRUE;
			}
		}
	}
	return FALSE;
}