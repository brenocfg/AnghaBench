#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zone {TYPE_1__* zone_pgdat; } ;
struct mem_cgroup_reclaim_cookie {int /*<<< orphan*/  priority; struct zone* zone; } ;
struct mem_cgroup {int /*<<< orphan*/  res; int /*<<< orphan*/  stat; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int MEM_CGROUP_MAX_RECLAIM_LOOPS ; 
 int /*<<< orphan*/  get_swappiness (struct mem_cgroup*) ; 
 unsigned long mem_cgroup_get_excess (struct mem_cgroup*) ; 
 struct mem_cgroup* mem_cgroup_iter (struct mem_cgroup*,struct mem_cgroup*,struct mem_cgroup_reclaim_cookie*) ; 
 int /*<<< orphan*/  mem_cgroup_iter_break (struct mem_cgroup*,struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_local_usage (int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_shrink_node_zone (struct mem_cgroup*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct zone*,int /*<<< orphan*/ ) ; 
 scalar_t__ res_counter_check_under_soft_limit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mem_cgroup_soft_reclaim(struct mem_cgroup *root_mem,
				   struct zone *zone,
				   gfp_t gfp_mask)
{
	struct mem_cgroup *victim = NULL;
	int total = 0;
	int loop = 0;
	unsigned long excess = mem_cgroup_get_excess(root_mem);
	struct mem_cgroup_reclaim_cookie reclaim = {
		.zone = zone,
		.priority = 0,
	};

	while (1) {
		victim = mem_cgroup_iter(root_mem, victim, &reclaim);
		if (!victim) {
			loop++;
			if (loop >= 2) {
				/*
				 * If we have not been able to reclaim
				 * anything, it might because there are
				 * no reclaimable pages under this hierarchy
				 */
				if (!total)
					break;
				/*
				 * We want to do more targetted reclaim.
				 * excess >> 2 is not to excessive so as to
				 * reclaim too much, nor too less that we keep
				 * coming back to reclaim from this cgroup
				 */
				if (total >= (excess >> 2) ||
					(loop > MEM_CGROUP_MAX_RECLAIM_LOOPS))
					break;
			}
			continue;
		}
		if (!mem_cgroup_local_usage(&victim->stat)) {
			/* this cgroup's local usage == 0 */
			continue;
		}

		total += mem_cgroup_shrink_node_zone(victim, gfp_mask, false,
						get_swappiness(victim), zone,
						zone->zone_pgdat->node_id);
		if (res_counter_check_under_soft_limit(&root_mem->res))
			break;
	}
	mem_cgroup_iter_break(root_mem, victim);
	return total;
}