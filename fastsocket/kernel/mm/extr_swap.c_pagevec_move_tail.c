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
struct page {int /*<<< orphan*/  lru; } ;
struct lruvec {int /*<<< orphan*/ * lists; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  PGROTATED ; 
 int /*<<< orphan*/  PageActive (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lruvec* mem_cgroup_lru_move_lists (struct zone*,struct page*,int,int) ; 
 int page_lru_base_type (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 
 int /*<<< orphan*/  release_pages (struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pagevec_move_tail(struct pagevec *pvec)
{
	int i;
	int pgmoved = 0;
	struct zone *zone = NULL;

	for (i = 0; i < pagevec_count(pvec); i++) {
		struct page *page = pvec->pages[i];
		struct zone *pagezone = page_zone(page);

		if (pagezone != zone) {
			if (zone)
				spin_unlock(&zone->lru_lock);
			zone = pagezone;
			spin_lock(&zone->lru_lock);
		}
		if (PageLRU(page) && !PageActive(page) && !PageUnevictable(page)) {
			enum lru_list lru = page_lru_base_type(page);
			struct lruvec *lruvec;

			lruvec = mem_cgroup_lru_move_lists(page_zone(page),
							   page, lru, lru);
			list_move_tail(&page->lru, &lruvec->lists[lru]);
			pgmoved++;
		}
	}
	if (zone)
		spin_unlock(&zone->lru_lock);
	__count_vm_events(PGROTATED, pgmoved);
	release_pages(pvec->pages, pvec->nr, pvec->cold);
	pagevec_reinit(pvec);
}