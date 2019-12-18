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
struct zone {long* lowmem_reserve; unsigned long* watermark; TYPE_1__* free_area; } ;
struct TYPE_2__ {int nr_free; } ;

/* Variables and functions */
 int ALLOC_HARDER ; 
 int ALLOC_HIGH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t WMARK_MIN ; 
 int pageblock_order ; 

__attribute__((used)) static bool __zone_watermark_ok(struct zone *z, int order, unsigned long mark,
		      int classzone_idx, int alloc_flags, long free_pages)
{
	/* free_pages my go negative - that's OK */
	long min = mark;
	int o;

	free_pages -= (1 << order) + 1;
	if (alloc_flags & ALLOC_HIGH)
		min -= min / 2;
	if (alloc_flags & ALLOC_HARDER)
		min -= min / 4;

	if (free_pages <= min + z->lowmem_reserve[classzone_idx])
		return false;
	if (!order)
		return true;

	/*
	 * Don't require any high order page under the min
	 * wmark. Invoking compaction to create lots of high order
	 * pages below the min wmark is wasteful because those
	 * hugepages cannot be allocated without PF_MEMALLOC and the
	 * PF_MEMALLOC paths must not depend on high order allocations
	 * to succeed.
	 */
	min = mark - z->watermark[WMARK_MIN];
	WARN_ON(min < 0);
	if (alloc_flags & ALLOC_HIGH)
		min -= min / 2;
	if (alloc_flags & ALLOC_HARDER)
		min -= min / 4;
	for (o = 0; o < order; o++) {
		/* At the next order, this order's pages become unavailable */
		free_pages -= z->free_area[o].nr_free << o;

		/* Require fewer higher order pages to be free */
		if (o < (pageblock_order >> 2))
			min >>= 1;

		if (free_pages <= min)
			return false;
	}
	return true;
}