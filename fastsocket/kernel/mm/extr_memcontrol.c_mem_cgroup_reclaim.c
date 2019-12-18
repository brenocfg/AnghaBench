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
struct mem_cgroup {scalar_t__ memsw_is_minimum; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int MEM_CGROUP_MAX_RECLAIM_LOOPS ; 
 unsigned long MEM_CGROUP_RECLAIM_NOSWAP ; 
 unsigned long MEM_CGROUP_RECLAIM_SHRINK ; 
 int /*<<< orphan*/  drain_all_stock_async () ; 
 int /*<<< orphan*/  get_swappiness (struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_check_under_limit (struct mem_cgroup*) ; 
 scalar_t__ try_to_free_mem_cgroup_pages (struct mem_cgroup*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long mem_cgroup_reclaim(struct mem_cgroup *memcg,
					gfp_t gfp_mask,
					unsigned long flags)
{
	unsigned long total = 0;
	bool noswap = false;
	int loop;

	if (flags & MEM_CGROUP_RECLAIM_NOSWAP)
		noswap = true;
	if (!(flags & MEM_CGROUP_RECLAIM_SHRINK) && memcg->memsw_is_minimum)
		noswap = true;

	for (loop = 0; loop < MEM_CGROUP_MAX_RECLAIM_LOOPS; loop++) {
		if (loop)
			drain_all_stock_async();
		total += try_to_free_mem_cgroup_pages(memcg, gfp_mask, noswap,
						      get_swappiness(memcg));
		/*
		 * Allow limit shrinkers, which are triggered directly
		 * by userspace, to catch signals and stop reclaim
		 * after minimal progress, regardless of the margin.
		 */
		if (total && (flags & MEM_CGROUP_RECLAIM_SHRINK))
			break;
		if (mem_cgroup_check_under_limit(memcg))
			break;
		/*
		 * If nothing was reclaimed after two attempts, there
		 * may be no reclaimable pages in this hierarchy.
		 */
		if (loop && !total)
			break;
	}
	return total;
}