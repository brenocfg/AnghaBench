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
struct pagevec {int /*<<< orphan*/  cold; int /*<<< orphan*/  nr; struct page** pages; } ;
struct page {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  PageActive (struct page*) ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  SetPageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct zone*,struct page*,int) ; 
 int is_active_lru (int) ; 
 int is_file_lru (int) ; 
 int /*<<< orphan*/  is_unevictable_lru (int) ; 
 struct zone* page_zone (struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 
 int /*<<< orphan*/  release_pages (struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_page_reclaim_stat (struct zone*,struct page*,int,int) ; 

void ____pagevec_lru_add(struct pagevec *pvec, enum lru_list lru)
{
	int i;
	struct zone *zone = NULL;

	VM_BUG_ON(is_unevictable_lru(lru));

	for (i = 0; i < pagevec_count(pvec); i++) {
		struct page *page = pvec->pages[i];
		struct zone *pagezone = page_zone(page);
		int file;
		int active;

		if (pagezone != zone) {
			if (zone)
				spin_unlock_irq(&zone->lru_lock);
			zone = pagezone;
			spin_lock_irq(&zone->lru_lock);
		}
		VM_BUG_ON(PageActive(page));
		VM_BUG_ON(PageUnevictable(page));
		VM_BUG_ON(PageLRU(page));
		SetPageLRU(page);
		active = is_active_lru(lru);
		file = is_file_lru(lru);
		if (active)
			SetPageActive(page);
		update_page_reclaim_stat(zone, page, file, active);
		add_page_to_lru_list(zone, page, lru);
	}
	if (zone)
		spin_unlock_irq(&zone->lru_lock);
	release_pages(pvec->pages, pvec->nr, pvec->cold);
	pagevec_reinit(pvec);
}