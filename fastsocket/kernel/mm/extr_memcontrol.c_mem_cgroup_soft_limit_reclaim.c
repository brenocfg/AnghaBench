#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zone {int dummy; } ;
struct mem_cgroup_tree_per_zone {int /*<<< orphan*/  lock; } ;
struct mem_cgroup_per_zone {TYPE_1__* mem; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  css; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int MEM_CGROUP_MAX_SOFT_LIMIT_RECLAIM_LOOPS ; 
 int /*<<< orphan*/  __mem_cgroup_insert_exceeded (TYPE_1__*,struct mem_cgroup_per_zone*,struct mem_cgroup_tree_per_zone*,unsigned long long) ; 
 struct mem_cgroup_per_zone* __mem_cgroup_largest_soft_limit_node (struct mem_cgroup_tree_per_zone*) ; 
 int /*<<< orphan*/  __mem_cgroup_remove_exceeded (TYPE_1__*,struct mem_cgroup_per_zone*,struct mem_cgroup_tree_per_zone*) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 struct mem_cgroup_per_zone* mem_cgroup_largest_soft_limit_node (struct mem_cgroup_tree_per_zone*) ; 
 unsigned long mem_cgroup_soft_reclaim (TYPE_1__*,struct zone*,int /*<<< orphan*/ ) ; 
 unsigned long long res_counter_soft_limit_excess (int /*<<< orphan*/ *) ; 
 struct mem_cgroup_tree_per_zone* soft_limit_tree_node_zone (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned long mem_cgroup_soft_limit_reclaim(struct zone *zone, int order,
						gfp_t gfp_mask, int nid,
						int zid)
{
	unsigned long nr_reclaimed = 0;
	struct mem_cgroup_per_zone *mz, *next_mz = NULL;
	unsigned long reclaimed;
	int loop = 0;
	struct mem_cgroup_tree_per_zone *mctz;
	unsigned long long excess;

	if (order > 0)
		return 0;

	mctz = soft_limit_tree_node_zone(nid, zid);
	/*
	 * This loop can run a while, specially if mem_cgroup's continuously
	 * keep exceeding their soft limit and putting the system under
	 * pressure
	 */
	do {
		if (next_mz)
			mz = next_mz;
		else
			mz = mem_cgroup_largest_soft_limit_node(mctz);
		if (!mz)
			break;

		reclaimed = mem_cgroup_soft_reclaim(mz->mem, zone, gfp_mask);
		nr_reclaimed += reclaimed;
		spin_lock(&mctz->lock);

		/*
		 * If we failed to reclaim anything from this memory cgroup
		 * it is time to move on to the next cgroup
		 */
		next_mz = NULL;
		if (!reclaimed) {
			do {
				/*
				 * Loop until we find yet another one.
				 *
				 * By the time we get the soft_limit lock
				 * again, someone might have aded the
				 * group back on the RB tree. Iterate to
				 * make sure we get a different mem.
				 * mem_cgroup_largest_soft_limit_node returns
				 * NULL if no other cgroup is present on
				 * the tree
				 */
				next_mz =
				__mem_cgroup_largest_soft_limit_node(mctz);
				if (next_mz == mz) {
					css_put(&next_mz->mem->css);
					next_mz = NULL;
				} else /* next_mz == NULL or other memcg */
					break;
			} while (1);
		}
		__mem_cgroup_remove_exceeded(mz->mem, mz, mctz);
		excess = res_counter_soft_limit_excess(&mz->mem->res);
		/*
		 * One school of thought says that we should not add
		 * back the node to the tree if reclaim returns 0.
		 * But our reclaim could return 0, simply because due
		 * to priority we are exposing a smaller subset of
		 * memory to reclaim from. Consider this as a longer
		 * term TODO.
		 */
		/* If excess == 0, no tree ops */
		__mem_cgroup_insert_exceeded(mz->mem, mz, mctz, excess);
		spin_unlock(&mctz->lock);
		css_put(&mz->mem->css);
		loop++;
		/*
		 * Could not reclaim anything and there are no more
		 * mem cgroups to try or we seem to be looping without
		 * reclaiming anything.
		 */
		if (!nr_reclaimed &&
			(next_mz == NULL ||
			loop > MEM_CGROUP_MAX_SOFT_LIMIT_RECLAIM_LOOPS))
			break;
	} while (!nr_reclaimed);
	if (next_mz)
		css_put(&next_mz->mem->css);
	return nr_reclaimed;
}