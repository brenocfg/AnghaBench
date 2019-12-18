#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page_cgroup {int dummy; } ;
struct page {int dummy; } ;
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  memsw; } ;
typedef  enum charge_type { ____Placeholder_charge_type } charge_type ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  __mem_cgroup_commit_charge (struct mem_cgroup*,struct page_cgroup*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_exclude_rmdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_release_and_wakeup_rmdir (int /*<<< orphan*/ *) ; 
 scalar_t__ do_swap_account ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 struct mem_cgroup* mem_cgroup_lookup (unsigned short) ; 
 int /*<<< orphan*/  mem_cgroup_lru_add_after_commit_swapcache (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_lru_del_before_commit_swapcache (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_put (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_swap_statistics (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  res_counter_uncharge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned short swap_cgroup_record (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mem_cgroup_commit_charge_swapin(struct page *page, struct mem_cgroup *ptr,
					enum charge_type ctype)
{
	struct page_cgroup *pc;

	if (mem_cgroup_disabled())
		return;
	if (!ptr)
		return;
	cgroup_exclude_rmdir(&ptr->css);
	pc = lookup_page_cgroup(page);
	mem_cgroup_lru_del_before_commit_swapcache(page);
	__mem_cgroup_commit_charge(ptr, pc, ctype, PAGE_SIZE);
	mem_cgroup_lru_add_after_commit_swapcache(page);
	/*
	 * Now swap is on-memory. This means this page may be
	 * counted both as mem and swap....double count.
	 * Fix it by uncharging from memsw. Basically, this SwapCache is stable
	 * under lock_page(). But in do_swap_page()::memory.c, reuse_swap_page()
	 * may call delete_from_swap_cache() before reach here.
	 */
	if (do_swap_account && PageSwapCache(page)) {
		swp_entry_t ent = {.val = page_private(page)};
		unsigned short id;
		struct mem_cgroup *memcg;

		id = swap_cgroup_record(ent, 0);
		rcu_read_lock();
		memcg = mem_cgroup_lookup(id);
		if (memcg) {
			/*
			 * This recorded memcg can be obsolete one. So, avoid
			 * calling css_tryget
			 */
			if (!mem_cgroup_is_root(memcg))
				res_counter_uncharge(&memcg->memsw, PAGE_SIZE);
			mem_cgroup_swap_statistics(memcg, false);
			mem_cgroup_put(memcg);
		}
		rcu_read_unlock();
	}
	/*
	 * At swapin, we may charge account against cgroup which has no tasks.
	 * So, rmdir()->pre_destroy() can be called while we do this charge.
	 * In that case, we need to call pre_destroy() again. check it here.
	 */
	cgroup_release_and_wakeup_rmdir(&ptr->css);
}