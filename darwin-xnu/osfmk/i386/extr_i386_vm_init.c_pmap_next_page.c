#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {scalar_t__ alloc_up; scalar_t__ alloc_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ avail_remaining ; 
 scalar_t__ lowest_lo ; 
 scalar_t__ max_ppnum ; 
 size_t pmap_memory_region_count ; 
 size_t pmap_memory_region_current ; 
 TYPE_1__* pmap_memory_regions ; 

boolean_t
pmap_next_page(
	       ppnum_t *pn)
{
	if (avail_remaining) while (pmap_memory_region_current < pmap_memory_region_count) {
		if (pmap_memory_regions[pmap_memory_region_current].alloc_up >
		    pmap_memory_regions[pmap_memory_region_current].alloc_down) {
			pmap_memory_region_current++;
			continue;
		}
		*pn = pmap_memory_regions[pmap_memory_region_current].alloc_up++;
		avail_remaining--;

		if (*pn > max_ppnum)
			max_ppnum = *pn;

		if (lowest_lo == 0 || *pn < lowest_lo)
			lowest_lo = *pn;

		return TRUE;
	}
	return FALSE;
}