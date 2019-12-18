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
struct page {int dummy; } ;
struct mem_cgroup_tree_per_zone {int /*<<< orphan*/  lock; } ;
struct mem_cgroup_per_zone {scalar_t__ on_tree; } ;
struct mem_cgroup {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_insert_exceeded (struct mem_cgroup*,struct mem_cgroup_per_zone*,struct mem_cgroup_tree_per_zone*,unsigned long long) ; 
 int /*<<< orphan*/  __mem_cgroup_remove_exceeded (struct mem_cgroup*,struct mem_cgroup_per_zone*,struct mem_cgroup_tree_per_zone*) ; 
 struct mem_cgroup_per_zone* mem_cgroup_zoneinfo (struct mem_cgroup*,int,int) ; 
 int page_to_nid (struct page*) ; 
 int page_zonenum (struct page*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 unsigned long long res_counter_soft_limit_excess (int /*<<< orphan*/ *) ; 
 struct mem_cgroup_tree_per_zone* soft_limit_tree_from_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mem_cgroup_update_tree(struct mem_cgroup *mem, struct page *page)
{
	unsigned long long excess;
	struct mem_cgroup_per_zone *mz;
	struct mem_cgroup_tree_per_zone *mctz;
	int nid = page_to_nid(page);
	int zid = page_zonenum(page);
	mctz = soft_limit_tree_from_page(page);

	/*
	 * Necessary to update all ancestors when hierarchy is used.
	 * because their event counter is not touched.
	 */
	for (; mem; mem = parent_mem_cgroup(mem)) {
		mz = mem_cgroup_zoneinfo(mem, nid, zid);
		excess = res_counter_soft_limit_excess(&mem->res);
		/*
		 * We have to update the tree if mz is on RB-tree or
		 * mem is over its softlimit.
		 */
		if (excess || mz->on_tree) {
			spin_lock(&mctz->lock);
			/* if on-tree, remove it */
			if (mz->on_tree)
				__mem_cgroup_remove_exceeded(mem, mz, mctz);
			/*
			 * Insert again. mz->usage_in_excess will be updated.
			 * If excess is 0, no tree ops.
			 */
			__mem_cgroup_insert_exceeded(mem, mz, mctz, excess);
			spin_unlock(&mctz->lock);
		}
	}
}