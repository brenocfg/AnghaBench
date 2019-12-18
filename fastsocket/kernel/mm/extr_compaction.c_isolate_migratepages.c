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
struct zone {int /*<<< orphan*/  lru_lock; int /*<<< orphan*/  zone_start_pfn; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
struct compact_control {unsigned long migrate_pfn; unsigned long free_pfn; int finished_update_migrate; unsigned long nr_migratepages; int /*<<< orphan*/  sync; struct list_head migratepages; } ;
typedef  int isolate_mode_t ;

/* Variables and functions */
 int ALIGN (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 unsigned long COMPACT_CLUSTER_MAX ; 
 int HZ ; 
 int ISOLATE_ACTIVE ; 
 int ISOLATE_ASYNC_MIGRATE ; 
 int ISOLATE_INACTIVE ; 
 int MAX_ORDER_NR_PAGES ; 
 scalar_t__ MIGRATE_MOVABLE ; 
 scalar_t__ PageBuddy (struct page*) ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageTransCompound (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 unsigned long SWAP_CLUSTER_MAX ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ __isolate_lru_page (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_isolated (struct zone*,int,struct compact_control*) ; 
 int compact_checklock_irqsave (int /*<<< orphan*/ *,unsigned long*,int,struct compact_control*) ; 
 int compound_order (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct zone*,struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  isolation_suitable (struct compact_control*,struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 unsigned long pageblock_nr_pages ; 
 unsigned long pageblock_order ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid_within (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  too_many_isolated (struct zone*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pageblock_skip (struct compact_control*,struct page*,unsigned long,int) ; 

__attribute__((used)) static unsigned long isolate_migratepages(struct zone *zone,
					struct compact_control *cc)
{
	unsigned long low_pfn, end_pfn;
	unsigned long last_pageblock_nr = 0, pageblock_nr;
	struct list_head *migratelist = &cc->migratepages;
	isolate_mode_t mode = ISOLATE_ACTIVE|ISOLATE_INACTIVE;
	unsigned long flags;
	bool locked;
	struct page *page = NULL, *valid_page = NULL;

	/* Do not scan outside zone boundaries */
	low_pfn = max(cc->migrate_pfn, zone->zone_start_pfn);

	/* Only scan within a pageblock boundary */
	end_pfn = ALIGN(low_pfn + pageblock_nr_pages, pageblock_nr_pages);

	/* Do not cross the free scanner or scan within a memory hole */
	if (end_pfn > cc->free_pfn || !pfn_valid(low_pfn)) {
		cc->migrate_pfn = end_pfn;
		return 0;
	}

	/*
	 * Ensure that there are not too many pages isolated from the LRU
	 * list by either parallel reclaimers or compaction. If there are,
	 * delay for some time until fewer pages are isolated
	 */
	while (unlikely(too_many_isolated(zone))) {
		congestion_wait(BLK_RW_ASYNC, HZ/10);

		if (fatal_signal_pending(current))
			return 0;
	}

	/* Time to isolate some pages for migration */
	cond_resched();
	spin_lock_irqsave(&zone->lru_lock, flags);
	locked = true;
	for (; low_pfn < end_pfn; low_pfn++) {
		/* give a chance to irqs before checking need_resched() */
		if (!((low_pfn+1) % SWAP_CLUSTER_MAX)) {
			spin_unlock_irqrestore(&zone->lru_lock, flags);
			locked = 0;
		}

		/* Check if it is ok to still hold the lock */
		locked = compact_checklock_irqsave(&zone->lru_lock, &flags,
								locked, cc);
		if (!locked)
			break;

		/*
		 * migrate_pfn does not necessarily start aligned to a
		 * pageblock. Ensure that pfn_valid is called when moving
		 * into a new MAX_ORDER_NR_PAGES range in case of large
		 * memory holes within the zone
		 */
		if ((low_pfn & (MAX_ORDER_NR_PAGES - 1)) == 0) {
			if (!pfn_valid(low_pfn)) {
				low_pfn += MAX_ORDER_NR_PAGES - 1;
				continue;
			}
		}

		if (!pfn_valid_within(low_pfn))
			continue;

		/*
		 * Get the page and ensure the page is within the same zone.
		 * See the comment in isolate_freepages about overlapping
		 * nodes. It is deliberate that the new zone lock is not taken
		 * as memory compaction should not move pages between nodes.
		 */
		page = pfn_to_page(low_pfn);
		if (page_zone(page) != zone)
			continue;

		if (!valid_page)
			valid_page = page;

		/* If isolation recently failed, do not retry */
		pageblock_nr = low_pfn >> pageblock_order;
		if (!isolation_suitable(cc, page))
			goto next_pageblock;

		/* Skip if free */
		if (PageBuddy(page))
			continue;

		/*
		 * For async migration, also only scan in MOVABLE blocks. Async
		 * migration is optimistic to see if the minimum amount of work
		 * satisfies the allocation
		 */
		if (!cc->sync && last_pageblock_nr != pageblock_nr &&
				get_pageblock_migratetype(page) != MIGRATE_MOVABLE) {
			low_pfn += pageblock_nr_pages;
			low_pfn = ALIGN(low_pfn, pageblock_nr_pages) - 1;
			last_pageblock_nr = pageblock_nr;
			cc->finished_update_migrate = true;
			continue;
		}

		if (!PageLRU(page))
			continue;

		/*
		 * PageLRU is set, and lru_lock excludes isolation,
		 * splitting and collapsing (collapsing has already
		 * happened if PageLRU is set).
		 */
		if (PageTransHuge(page)) {
			low_pfn += (1 << compound_order(page)) - 1;
			continue;
		}

		if (!cc->sync)
			mode |= ISOLATE_ASYNC_MIGRATE;

		/* Try isolate the page */
		if (__isolate_lru_page(page, mode, 0) != 0)
			continue;

		VM_BUG_ON(PageTransCompound(page));

		/* Successfully isolated */
		cc->finished_update_migrate = true;
		del_page_from_lru_list(zone, page, page_lru(page));
		list_add(&page->lru, migratelist);
		cc->nr_migratepages++;

		/* Avoid isolating too much */
		if (cc->nr_migratepages == COMPACT_CLUSTER_MAX)
			break;

		continue;

next_pageblock:
		low_pfn += pageblock_nr_pages;
		low_pfn = ALIGN(low_pfn, pageblock_nr_pages) - 1;
		last_pageblock_nr = pageblock_nr;
	}

	acct_isolated(zone, locked, cc);

	if (locked)
		spin_unlock_irqrestore(&zone->lru_lock, flags);

	/* Update the pageblock-skip if the whole pageblock was scanned */
	if (low_pfn == end_pfn)
		update_pageblock_skip(cc, valid_page, cc->nr_migratepages, true);

	cc->migrate_pfn = low_pfn;
	return cc->nr_migratepages;
}