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
struct pagevec {int dummy; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct lruvec {int /*<<< orphan*/ * lists; } ;
struct list_head {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int NR_LRU_BASE ; 
 int /*<<< orphan*/  PGDEACTIVATE ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,int,unsigned long) ; 
 int /*<<< orphan*/  __pagevec_release (struct pagevec*) ; 
 scalar_t__ buffer_heads_over_limit ; 
 scalar_t__ hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  is_active_lru (int) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* lru_to_page (struct list_head*) ; 
 struct lruvec* mem_cgroup_lru_add_list (struct zone*,struct page*,int) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int) ; 
 int /*<<< orphan*/  pagevec_strip (struct pagevec*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void move_active_pages_to_lru(struct zone *zone,
				     struct list_head *list,
				     enum lru_list lru)
{
	unsigned long pgmoved = 0;
	struct pagevec pvec;
	struct page *page;

	pagevec_init(&pvec, 1);

	while (!list_empty(list)) {
		struct lruvec *lruvec;

		page = lru_to_page(list);

		VM_BUG_ON(PageLRU(page));
		SetPageLRU(page);

		lruvec = mem_cgroup_lru_add_list(zone, page, lru);
		list_move(&page->lru, &lruvec->lists[lru]);
		pgmoved += hpage_nr_pages(page);

		if (!pagevec_add(&pvec, page) || list_empty(list)) {
			spin_unlock_irq(&zone->lru_lock);
			if (buffer_heads_over_limit)
				pagevec_strip(&pvec);
			__pagevec_release(&pvec);
			spin_lock_irq(&zone->lru_lock);
		}
	}
	__mod_zone_page_state(zone, NR_LRU_BASE + lru, pgmoved);
	if (!is_active_lru(lru))
		__count_vm_events(PGDEACTIVATE, pgmoved);
}