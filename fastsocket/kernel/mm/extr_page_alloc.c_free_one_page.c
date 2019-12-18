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
struct zone {int /*<<< orphan*/  lock; scalar_t__ pages_scanned; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  ZONE_ALL_UNRECLAIMABLE ; 
 int /*<<< orphan*/  __free_one_page (struct page*,struct zone*,int,int) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watermark_check_zone (struct zone*) ; 
 int /*<<< orphan*/  zone_clear_flag (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_one_page(struct zone *zone, struct page *page, int order,
				int migratetype)
{
	spin_lock(&zone->lock);
	zone_clear_flag(zone, ZONE_ALL_UNRECLAIMABLE);
	zone->pages_scanned = 0;

	__free_one_page(page, zone, order, migratetype);
	__mod_zone_page_state(zone, NR_FREE_PAGES, 1 << order);
	spin_unlock(&zone->lock);
	/* A batch of pages have been freed so check zone pressure */
	watermark_check_zone(zone);
}