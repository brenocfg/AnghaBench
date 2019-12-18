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
struct page_cgroup {int dummy; } ;
struct page {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  PageCgroupAcctLRU (struct page_cgroup*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct zone*,struct page*,int) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct zone*,struct page*,int) ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 int page_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mem_cgroup_lru_add_after_commit_swapcache(struct page *page)
{
	enum lru_list lru;
	unsigned long flags;
	struct zone *zone = page_zone(page);
	struct page_cgroup *pc = lookup_page_cgroup(page);

	spin_lock_irqsave(&zone->lru_lock, flags);
	lru = page_lru(page);
	/*
	 * If the page is not on the LRU, someone will soon put it
	 * there.  If it is, and also already accounted for on the
	 * memcg-side, it must be on the right lruvec as setting
	 * pc->mem_cgroup and PageCgroupUsed is properly ordered.
	 * Otherwise, root_mem_cgroup has been babysitting the page
	 * during the charge.  Move it to the new memcg now.
	 */
	if (PageLRU(page) && !PageCgroupAcctLRU(pc)) {
		del_page_from_lru_list(zone, page, lru);
		add_page_to_lru_list(zone, page, lru);
	}
	spin_unlock_irqrestore(&zone->lru_lock, flags);
}