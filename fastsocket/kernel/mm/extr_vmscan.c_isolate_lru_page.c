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
struct zone {int /*<<< orphan*/  lru_lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageLRU (struct page*) ; 
 int EBUSY ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct zone*,struct page*,int) ; 
 scalar_t__ get_page_unless_zero (struct page*) ; 
 int page_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int isolate_lru_page(struct page *page)
{
	int ret = -EBUSY;

	if (PageLRU(page)) {
		struct zone *zone = page_zone(page);

		spin_lock_irq(&zone->lru_lock);
		if (PageLRU(page) && get_page_unless_zero(page)) {
			int lru = page_lru(page);
			ret = 0;
			ClearPageLRU(page);

			del_page_from_lru_list(zone, page, lru);
		}
		spin_unlock_irq(&zone->lru_lock);
	}
	return ret;
}