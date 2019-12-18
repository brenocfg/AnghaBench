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
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MIGRATE_MOVABLE ; 
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int low_wmark_pages (struct zone*) ; 
 unsigned int page_order (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pageblock_nr_pages ; 
 int pageblock_order ; 
 int /*<<< orphan*/  rmv_page_order (struct page*) ; 
 int /*<<< orphan*/  set_page_refcounted (struct page*) ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 
 int /*<<< orphan*/  zone_watermark_ok (struct zone*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int split_free_page(struct page *page)
{
	unsigned int order;
	unsigned long watermark;
	struct zone *zone;

	BUG_ON(!PageBuddy(page));

	zone = page_zone(page);
	order = page_order(page);

	/* Obey watermarks as if the page was being allocated */
	watermark = low_wmark_pages(zone) + (1 << order);
	if (!zone_watermark_ok(zone, 0, watermark, 0, 0))
		return 0;

	/* Remove page from free list */
	list_del(&page->lru);
	zone->free_area[order].nr_free--;
	rmv_page_order(page);
	__mod_zone_page_state(zone, NR_FREE_PAGES, -(1UL << order));

	/* Split into individual pages */
	set_page_refcounted(page);
	split_page(page, order);

	if (order >= pageblock_order - 1) {
		struct page *endpage = page + (1 << order) - 1;
		for (; page < endpage; page += pageblock_nr_pages)
			set_pageblock_migratetype(page, MIGRATE_MOVABLE);
	}

	return 1 << order;
}