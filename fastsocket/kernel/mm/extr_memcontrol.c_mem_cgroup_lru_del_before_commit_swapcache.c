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
 scalar_t__ PageCgroupAcctLRU (struct page_cgroup*) ; 
 int /*<<< orphan*/  PageCgroupUsed (struct page_cgroup*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct zone*,struct page*,int) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct zone*,struct page*,int) ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 int page_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mem_cgroup_lru_del_before_commit_swapcache(struct page *page)
{
	enum lru_list lru;
	unsigned long flags;
	struct zone *zone = page_zone(page);
	struct page_cgroup *pc = lookup_page_cgroup(page);

	spin_lock_irqsave(&zone->lru_lock, flags);
	lru = page_lru(page);
	/*
	 * The uncharged page could still be registered to the LRU of
	 * the stale pc->mem_cgroup.
	 *
	 * As pc->mem_cgroup is about to get overwritten, the old LRU
	 * accounting needs to be taken care of.  Let root_mem_cgroup
	 * babysit the page until the new memcg is responsible for it.
	 *
	 * The PCG_USED bit is guarded by lock_page() as the page is
	 * swapcache/pagecache.
	 */
	if (PageLRU(page) && PageCgroupAcctLRU(pc) && !PageCgroupUsed(pc)) {
		del_page_from_lru_list(zone, page, lru);
		add_page_to_lru_list(zone, page, lru);
	}
	spin_unlock_irqrestore(&zone->lru_lock, flags);
}