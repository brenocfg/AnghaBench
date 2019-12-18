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
struct zone {unsigned long zone_start_pfn; unsigned long spanned_pages; unsigned long compact_cached_migrate_pfn; unsigned long compact_cached_free_pfn; } ;
struct compact_control {unsigned long migrate_pfn; unsigned long free_pfn; scalar_t__ sync; unsigned long nr_migratepages; scalar_t__ nr_freepages; int /*<<< orphan*/  freepages; int /*<<< orphan*/  migratepages; scalar_t__ contended; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPACTBLOCKS ; 
 int /*<<< orphan*/  COMPACTPAGEFAILED ; 
 int /*<<< orphan*/  COMPACTPAGES ; 
#define  COMPACT_CONTINUE 130 
#define  COMPACT_PARTIAL 129 
#define  COMPACT_SKIPPED 128 
 int /*<<< orphan*/  MIGRATE_ASYNC ; 
 scalar_t__ MIGRATE_SYNC ; 
 int /*<<< orphan*/  MIGRATE_SYNC_LIGHT ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __reset_isolation_suitable (struct zone*) ; 
 int compact_finished (struct zone*,struct compact_control*) ; 
 int /*<<< orphan*/  compaction_alloc ; 
 scalar_t__ compaction_restarting (struct zone*,int /*<<< orphan*/ ) ; 
 int compaction_suitable (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_events (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  current_is_kswapd () ; 
 int /*<<< orphan*/  isolate_migratepages (struct zone*,struct compact_control*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  migrate_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migrate_prep_local () ; 
 int pageblock_nr_pages ; 
 int /*<<< orphan*/  putback_lru_pages (int /*<<< orphan*/ *) ; 
 scalar_t__ release_freepages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_nr_listpages (struct compact_control*) ; 

__attribute__((used)) static int compact_zone(struct zone *zone, struct compact_control *cc)
{
	int ret;
	unsigned long start_pfn = zone->zone_start_pfn;
	unsigned long end_pfn = zone->zone_start_pfn + zone->spanned_pages;

	ret = compaction_suitable(zone, cc->order);
	switch (ret) {
	case COMPACT_PARTIAL:
	case COMPACT_SKIPPED:
		/* Compaction is likely to fail */
		return ret;
	case COMPACT_CONTINUE:
		/* Fall through to compaction */
		;
	}

	/*
	 * Clear pageblock skip if there were failures recently and
	 * compaction is about to be retried after being
	 * deferred. kswapd does not do this reset and it will wait
	 * direct compaction to do so either when the cursor meets
	 * after one compaction pass is complete or if compaction is
	 * restarted after being deferred for a while.
	 */
	if ((compaction_restarting(zone, cc->order)) && !current_is_kswapd())
		__reset_isolation_suitable(zone);

	/*
	 * Setup to move all movable pages to the end of the zone. Used cached
	 * information on where the scanners should start but check that it
	 * is initialised by ensuring the values are within zone boundaries.
	 */
	cc->migrate_pfn = zone->compact_cached_migrate_pfn;
	cc->free_pfn = zone->compact_cached_free_pfn;
	if (cc->free_pfn < start_pfn || cc->free_pfn > end_pfn) {
		cc->free_pfn = end_pfn & ~(pageblock_nr_pages-1);
		zone->compact_cached_free_pfn = cc->free_pfn;
	}
	if (cc->migrate_pfn < start_pfn || cc->migrate_pfn > end_pfn) {
		cc->migrate_pfn = start_pfn;
		zone->compact_cached_migrate_pfn = cc->migrate_pfn;
	}

	migrate_prep_local();

	while ((ret = compact_finished(zone, cc)) == COMPACT_CONTINUE) {
		unsigned long nr_migrate, nr_remaining;

		if (!isolate_migratepages(zone, cc)) {
			if (cc->contended && cc->sync != MIGRATE_SYNC) {
				putback_lru_pages(&cc->migratepages);
				cc->nr_migratepages = 0;
				ret = COMPACT_PARTIAL;
				break;
			}
			continue;
		}

		nr_migrate = cc->nr_migratepages;
		migrate_pages(&cc->migratepages, compaction_alloc,
				(unsigned long)cc, false,
				cc->sync ? MIGRATE_SYNC_LIGHT : MIGRATE_ASYNC);
		update_nr_listpages(cc);
		nr_remaining = cc->nr_migratepages;

		count_vm_event(COMPACTBLOCKS);
		count_vm_events(COMPACTPAGES, nr_migrate - nr_remaining);
		if (nr_remaining)
			count_vm_events(COMPACTPAGEFAILED, nr_remaining);

		/* Release LRU pages not migrated */
		if (!list_empty(&cc->migratepages)) {
			putback_lru_pages(&cc->migratepages);
			cc->nr_migratepages = 0;
		}

	}

	/* Release free pages and check accounting */
	cc->nr_freepages -= release_freepages(&cc->freepages);
	VM_BUG_ON(cc->nr_freepages != 0);

	return ret;
}