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
typedef  int u64 ;
struct mem_cgroup {int swappiness; int /*<<< orphan*/  reclaim_param_lock; scalar_t__ use_hierarchy; } ;
struct cgroup {int /*<<< orphan*/  children; struct cgroup* parent; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cgroup_lock () ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mem_cgroup_swappiness_write(struct cgroup *cgrp, struct cftype *cft,
				       u64 val)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cgrp);
	struct mem_cgroup *parent;

	if (val > 100)
		return -EINVAL;

	if (cgrp->parent == NULL)
		return -EINVAL;

	parent = mem_cgroup_from_cont(cgrp->parent);

	cgroup_lock();

	/* If under hierarchy, only empty-root can set this value */
	if ((parent->use_hierarchy) ||
	    (memcg->use_hierarchy && !list_empty(&cgrp->children))) {
		cgroup_unlock();
		return -EINVAL;
	}

	spin_lock(&memcg->reclaim_param_lock);
	memcg->swappiness = val;
	spin_unlock(&memcg->reclaim_param_lock);

	cgroup_unlock();

	return 0;
}