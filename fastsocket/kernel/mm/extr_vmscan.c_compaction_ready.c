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
struct zone {int present_pages; } ;
struct scan_control {unsigned long order; } ;

/* Variables and functions */
 int KSWAPD_ZONE_BALANCE_GAP_RATIO ; 
 unsigned long PAGE_ALLOC_COSTLY_ORDER ; 
 scalar_t__ compaction_deferred (struct zone*) ; 
 int /*<<< orphan*/  compaction_suitable (struct zone*,unsigned long) ; 
 unsigned long high_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  low_wmark_pages (struct zone*) ; 
 unsigned long min (int /*<<< orphan*/ ,int) ; 
 int zone_watermark_ok_safe (struct zone*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool compaction_ready(struct zone *zone, struct scan_control *sc)
{
	unsigned long balance_gap, watermark;
	bool watermark_ok;

	/* Do not consider compaction for orders reclaim is meant to satisfy */
	if (sc->order <= PAGE_ALLOC_COSTLY_ORDER)
		return false;

	/*
	 * Compaction takes time to run and there are potentially other
	 * callers using the pages just freed. Continue reclaiming until
	 * there is a buffer of free pages available to give compaction
	 * a reasonable chance of completing and allocating the page
	 */
	balance_gap = min(low_wmark_pages(zone),
		(zone->present_pages + KSWAPD_ZONE_BALANCE_GAP_RATIO-1) /
			KSWAPD_ZONE_BALANCE_GAP_RATIO);
	watermark = high_wmark_pages(zone) + balance_gap + (2UL << sc->order);
	watermark_ok = zone_watermark_ok_safe(zone, 0, watermark, 0, 0);

	/*
	 * If compaction is deferred, reclaim up to a point where
	 * compaction will have a chance of success when re-enabled
	 */
	if (compaction_deferred(zone))
		return watermark_ok;

	/* If compaction is not ready to start, keep reclaiming */
	if (!compaction_suitable(zone, sc->order))
		return false;

	return watermark_ok;
}