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
struct page_cgroup {struct mem_cgroup* mem_cgroup; } ;
struct page {int /*<<< orphan*/  mapping; } ;
struct mem_cgroup {int dummy; } ;
typedef  enum charge_type { ____Placeholder_charge_type } charge_type ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageCgroupUsed (struct page_cgroup*) ; 
#define  MEM_CGROUP_CHARGE_TYPE_DROP 130 
#define  MEM_CGROUP_CHARGE_TYPE_MAPPED 129 
#define  MEM_CGROUP_CHARGE_TYPE_SWAPOUT 128 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageCgroupMigration (struct page_cgroup*) ; 
 int /*<<< orphan*/  PageCgroupUsed (struct page_cgroup*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __do_uncharge (struct mem_cgroup*,int,int) ; 
 int compound_order (struct page*) ; 
 scalar_t__ do_swap_account ; 
 int /*<<< orphan*/  lock_page_cgroup (struct page_cgroup*) ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_charge_statistics (struct mem_cgroup*,struct page_cgroup*,int) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  mem_cgroup_get (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_soft_limit_check (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_swap_statistics (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_update_tree (struct mem_cgroup*,struct page*) ; 
 int /*<<< orphan*/  page_is_file_cache (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page_cgroup (struct page_cgroup*) ; 

__attribute__((used)) static struct mem_cgroup *
__mem_cgroup_uncharge_common(struct page *page, enum charge_type ctype)
{
	struct page_cgroup *pc;
	struct mem_cgroup *mem = NULL;
	int page_size = PAGE_SIZE;

	if (mem_cgroup_disabled())
		return NULL;

	if (PageSwapCache(page))
		return NULL;

	if (PageTransHuge(page)) {
		page_size <<= compound_order(page);
		VM_BUG_ON(!PageTransHuge(page));
	}

	/*
	 * Check if our page_cgroup is valid
	 */
	pc = lookup_page_cgroup(page);
	if (unlikely(!pc || !PageCgroupUsed(pc)))
		return NULL;

	lock_page_cgroup(pc);

	mem = pc->mem_cgroup;

	if (!PageCgroupUsed(pc))
		goto unlock_out;

	switch (ctype) {
	case MEM_CGROUP_CHARGE_TYPE_MAPPED:
	case MEM_CGROUP_CHARGE_TYPE_DROP:
		/* See mem_cgroup_prepare_migration() */
		if (page_mapped(page) || PageCgroupMigration(pc))
			goto unlock_out;
		break;
	case MEM_CGROUP_CHARGE_TYPE_SWAPOUT:
		if (!PageAnon(page)) {	/* Shared memory */
			if (page->mapping && !page_is_file_cache(page))
				goto unlock_out;
		} else if (page_mapped(page)) /* Anon */
				goto unlock_out;
		break;
	default:
		break;
	}

	mem_cgroup_charge_statistics(mem, pc, -page_size);

	ClearPageCgroupUsed(pc);
	/*
	 * pc->mem_cgroup is not cleared here. It will be accessed when it's
	 * freed from LRU. This is safe because uncharged page is expected not
	 * to be reused (freed soon). Exception is SwapCache, it's handled by
	 * special functions.
	 */
	unlock_page_cgroup(pc);
	/*
	 * even after unlock, we have memcg->res.usage here and this memcg
	 * will never be freed.
	 */
	if (mem_cgroup_soft_limit_check(mem))
		mem_cgroup_update_tree(mem, page);
	if (do_swap_account && ctype == MEM_CGROUP_CHARGE_TYPE_SWAPOUT) {
		mem_cgroup_swap_statistics(mem, true);
		mem_cgroup_get(mem);
	}
	if (!mem_cgroup_is_root(mem))
		__do_uncharge(mem, ctype, page_size);

	return mem;

unlock_out:
	unlock_page_cgroup(pc);
	return NULL;
}