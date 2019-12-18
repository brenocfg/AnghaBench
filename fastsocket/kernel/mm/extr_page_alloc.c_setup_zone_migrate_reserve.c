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
struct zone {unsigned long zone_start_pfn; unsigned long spanned_pages; int nr_migrate_reserve_block; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long MIGRATE_MOVABLE ; 
 unsigned long MIGRATE_RESERVE ; 
 scalar_t__ PageReserved (struct page*) ; 
 unsigned long get_pageblock_migratetype (struct page*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  min_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  move_freepages_block (struct zone*,struct page*,unsigned long) ; 
 scalar_t__ page_to_nid (struct page*) ; 
 scalar_t__ pageblock_nr_pages ; 
 int pageblock_order ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int roundup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ zone_to_nid (struct zone*) ; 

__attribute__((used)) static void setup_zone_migrate_reserve(struct zone *zone)
{
	unsigned long start_pfn, pfn, end_pfn;
	struct page *page;
	unsigned long block_migratetype;
	int reserve;
	bool anyblock = false;
	int old_reserve;
	int new_reserve;

retry:
	/* Get the start pfn, end pfn and the number of blocks to reserve */
	start_pfn = zone->zone_start_pfn;
	end_pfn = start_pfn + zone->spanned_pages;
	reserve = roundup(min_wmark_pages(zone), pageblock_nr_pages) >>
							pageblock_order;

	/*
	 * Reserve blocks are generally in place to help high-order atomic
	 * allocations that are short-lived. A min_free_kbytes value that
	 * would result in more than 2 reserve blocks for atomic allocations
	 * is assumed to be in place to help anti-fragmentation for the
	 * future allocation of hugepages at runtime.
	 */
	reserve = new_reserve = min(2, reserve);
	old_reserve = zone->nr_migrate_reserve_block;

	/* When memory hot-add, we almost always need to do nothing */
	if (reserve == old_reserve)
		return;

	for (pfn = start_pfn; pfn < end_pfn; pfn += pageblock_nr_pages) {
		if (!pfn_valid(pfn))
			continue;
		page = pfn_to_page(pfn);

		/* Watch out for overlapping nodes */
		if (page_to_nid(page) != zone_to_nid(zone))
			continue;

		/* Blocks with reserved pages will never free, skip them. */
		if (PageReserved(page))
			continue;

		block_migratetype = get_pageblock_migratetype(page);

		/* If this block is reserved, account for it */
		if (reserve > 0 && block_migratetype == MIGRATE_RESERVE) {
			reserve--;
			continue;
		}

		/* Suitable for reserving if this block is movable */
		if (reserve > 0) {
			if (anyblock || block_migratetype == MIGRATE_MOVABLE) {
				set_pageblock_migratetype(page, MIGRATE_RESERVE);
				move_freepages_block(zone, page, MIGRATE_RESERVE);
				reserve--;
				continue;
			}
		} else if (!old_reserve && !anyblock) {
			/*
			 * At boot time we don't need to scan the whole zone
			 * for turning off MIGRATE_RESERVE.
			 * Note: when anyblock is true, we can't exit a loop and
			 * turn off MIGRATE_RESERVE which turn on pass-1.
			 */
			break;
		}

		/*
		 * If the reserve is met and this is a previous reserved block,
		 * take it back
		 */
		if (block_migratetype == MIGRATE_RESERVE) {
			set_pageblock_migratetype(page, MIGRATE_MOVABLE);
			move_freepages_block(zone, page, MIGRATE_MOVABLE);
		}
	}

	/*
	 * Ideally when selecting new MIGRATE_RESERVE blocks, an existing
	 * movable block is used to maximise available pages in the reserve
	 * block. Very early in boot, this is not an option so if the reserve
	 * is not met first time around, try again but allow any block to be
	 * used
	 */
	if (unlikely(reserve) && !anyblock) {
		anyblock = true;
		goto retry;
	}

	zone->nr_migrate_reserve_block = new_reserve;
}