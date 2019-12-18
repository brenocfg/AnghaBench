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
struct zone {TYPE_1__* free_area; } ;
struct compact_control {scalar_t__ free_pfn; scalar_t__ migrate_pfn; int order; size_t migratetype; } ;
struct TYPE_2__ {scalar_t__ nr_free; int /*<<< orphan*/ * free_list; } ;

/* Variables and functions */
 int COMPACT_COMPLETE ; 
 int COMPACT_CONTINUE ; 
 int COMPACT_PARTIAL ; 
 unsigned int MAX_ORDER ; 
 int /*<<< orphan*/  __reset_isolation_suitable (struct zone*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_is_kswapd () ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 unsigned long low_wmark_pages (struct zone*) ; 
 unsigned int pageblock_order ; 
 int /*<<< orphan*/  zone_watermark_ok (struct zone*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compact_finished(struct zone *zone,
			    struct compact_control *cc)
{
	unsigned int order;
	unsigned long watermark;

	if (fatal_signal_pending(current))
		return COMPACT_PARTIAL;

	/* Compaction run completes if the migrate and free scanner meet */
	if (cc->free_pfn <= cc->migrate_pfn) {
		/*
		 * Clear the PG_migrate_skip information. kswapd does
		 * not clear it as the decision to be clear should be
		 * directly based on an allocation request.
		 */
		if (!current_is_kswapd())
			__reset_isolation_suitable(zone);

		return COMPACT_COMPLETE;
	}

	/*
	 * order == -1 is expected when compacting via
	 * /proc/sys/vm/compact_memory
	 */
	if (cc->order == -1)
		return COMPACT_CONTINUE;

	/* Compaction run is not finished if the watermark is not met */
	watermark = low_wmark_pages(zone);
	watermark += (1 << cc->order);

	if (!zone_watermark_ok(zone, cc->order, watermark, 0, 0))
		return COMPACT_CONTINUE;

	/* Direct compactor: Is a suitable page free? */
	for (order = cc->order; order < MAX_ORDER; order++) {
		/* Job done if page is free of the right migratetype */
		if (!list_empty(&zone->free_area[order].free_list[cc->migratetype]))
			return COMPACT_PARTIAL;

		/* Job done if allocation would set block type */
		if (order >= pageblock_order && zone->free_area[order].nr_free)
			return COMPACT_PARTIAL;
	}

	return COMPACT_CONTINUE;
}