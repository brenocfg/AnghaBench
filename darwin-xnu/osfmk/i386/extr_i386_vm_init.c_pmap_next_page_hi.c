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
typedef  scalar_t__ ppnum_t ;
struct TYPE_3__ {scalar_t__ alloc_down; scalar_t__ alloc_up; } ;
typedef  TYPE_1__ pmap_memory_region_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ avail_remaining ; 
 scalar_t__ highest_hi ; 
 scalar_t__ lowest_hi ; 
 scalar_t__ lowest_lo ; 
 scalar_t__ max_ppnum ; 
 int pmap_memory_region_count ; 
 TYPE_1__* pmap_memory_regions ; 
 scalar_t__ pmap_next_page_reserved (scalar_t__*) ; 

boolean_t
pmap_next_page_hi(
	          ppnum_t *pn)
{
	pmap_memory_region_t *region;
	int	n;

	if (pmap_next_page_reserved(pn))
		return TRUE;

	if (avail_remaining) {
		for (n = pmap_memory_region_count - 1; n >= 0; n--) {
			region = &pmap_memory_regions[n];

			if (region->alloc_down >= region->alloc_up) {
				*pn = region->alloc_down--;
				avail_remaining--;

				if (*pn > max_ppnum)
					max_ppnum = *pn;

                                if (lowest_lo == 0 || *pn < lowest_lo)
                                        lowest_lo = *pn;

                                if (lowest_hi == 0 || *pn < lowest_hi)
                                        lowest_hi = *pn;

                                if (*pn > highest_hi)
                                        highest_hi = *pn;

				return TRUE;
			}
		}
	}
	return FALSE;
}