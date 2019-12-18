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
struct zone {unsigned long zone_start_pfn; unsigned long spanned_pages; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
struct compact_control {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pageblock_nr_pages ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid_within (unsigned long) ; 
 int split_free_page (struct page*) ; 
 int /*<<< orphan*/  update_pageblock_skip (struct compact_control*,struct page*,int,int) ; 

__attribute__((used)) static unsigned long isolate_freepages_block(struct compact_control *cc,
				struct zone *zone,
				unsigned long blockpfn,
				struct list_head *freelist)
{
	unsigned long zone_end_pfn, end_pfn;
	int total_isolated = 0;
	struct page *cursor, *valid_page = NULL;

	/* Get the last PFN we should scan for free pages at */
	zone_end_pfn = zone->zone_start_pfn + zone->spanned_pages;

	/*
	 * As pfn may not start aligned, pfn+pageblock_nr_page
	 * may cross a MAX_ORDER_NR_PAGES boundary and miss
	 * a pfn_valid check. Ensure isolate_freepages_block()
	 * only scans within a pageblock
	 */
	end_pfn = ALIGN(blockpfn + 1, pageblock_nr_pages);
	end_pfn = min(end_pfn, zone_end_pfn);

	/* Find the first usable PFN in the block to initialse page cursor */
	for (; blockpfn < end_pfn; blockpfn++) {
		if (pfn_valid_within(blockpfn))
			break;
	}
	cursor = pfn_to_page(blockpfn);

	/* Isolate free pages. This assumes the block is valid */
	for (; blockpfn < end_pfn; blockpfn++, cursor++) {
		int isolated, i;
		struct page *page = cursor;

		if (!pfn_valid_within(blockpfn))
			continue;

		if (!valid_page)
			valid_page = page;

		if (!PageBuddy(page))
			continue;

		/* Found a free page, break it into order-0 pages */
		isolated = split_free_page(page);
		total_isolated += isolated;
		for (i = 0; i < isolated; i++) {
			list_add(&page->lru, freelist);
			page++;
		}

		/* If a page was split, advance to the end of it */
		if (isolated) {
			blockpfn += isolated - 1;
			cursor += isolated - 1;
		}
	}

	/* Update the pageblock-skip if the whole pageblock was scanned */
	if (blockpfn == end_pfn)
		update_pageblock_skip(cc, valid_page, total_isolated, false);

	return total_isolated;
}