#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct zone {int dummy; } ;
struct scan_control {int gfp_mask; unsigned long order; unsigned long nr_reclaimed; } ;

/* Variables and functions */
#define  COMPACT_CONTINUE 129 
#define  COMPACT_PARTIAL 128 
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int __GFP_REPEAT ; 
 int compaction_suitable (struct zone*,unsigned long) ; 
 int /*<<< orphan*/  in_reclaim_compaction (int,struct scan_control*) ; 
 scalar_t__ nr_swap_pages ; 
 unsigned long zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool should_continue_reclaim(struct zone *zone,
					unsigned long nr_reclaimed,
					unsigned long nr_scanned,
					int priority,
					struct scan_control *sc)
{
	unsigned long pages_for_compaction;
	unsigned long inactive_lru_pages;

	/* If not in reclaim/compaction mode, stop */
	if (!in_reclaim_compaction(priority, sc))
		return false;

	/* Consider stopping depending on scan and reclaim activity */
	if (sc->gfp_mask & __GFP_REPEAT) {
		/*
		 * For __GFP_REPEAT allocations, stop reclaiming if the
		 * full LRU list has been scanned and we are still failing
		 * to reclaim pages. This full LRU scan is potentially
		 * expensive but a __GFP_REPEAT caller really wants to succeed
		 */
		if (!nr_reclaimed && !nr_scanned)
			return false;
	} else {
		/*
		 * For non-__GFP_REPEAT allocations which can presumably
		 * fail without consequence, stop if we failed to reclaim
		 * any pages from the last SWAP_CLUSTER_MAX number of
		 * pages that were scanned. This will return to the
		 * caller faster at the risk reclaim/compaction and
		 * the resulting allocation attempt fails
		 */
		if (!nr_reclaimed)
			return false;
	}

	/*
	 * If we have not reclaimed enough pages for compaction and the
	 * inactive lists are large enough, continue reclaiming
	 */
	pages_for_compaction = (2UL << sc->order);
	inactive_lru_pages = zone_page_state(zone, NR_INACTIVE_FILE);
	if (nr_swap_pages > 0)
		inactive_lru_pages += zone_page_state(zone, NR_INACTIVE_ANON);
	if (sc->nr_reclaimed < pages_for_compaction &&
			inactive_lru_pages > pages_for_compaction)
		return true;

	/* If compaction would go ahead or the allocation would succeed, stop */
	switch (compaction_suitable(zone, sc->order)) {
	case COMPACT_PARTIAL:
	case COMPACT_CONTINUE:
		return false;
	default:
		return true;
	}
}