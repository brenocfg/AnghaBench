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
struct mem_cgroup {int oom_kill_disable; scalar_t__ use_hierarchy; } ;
struct cgroup {int /*<<< orphan*/  children; struct cgroup* parent; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cgroup_lock () ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 

__attribute__((used)) static int mem_cgroup_oom_control_write(struct cgroup *cgrp,
	struct cftype *cft, u64 val)
{
	struct mem_cgroup *mem = mem_cgroup_from_cont(cgrp);
	struct mem_cgroup *parent;

	/* cannot set to root cgroup and only 0 and 1 are allowed */
	if (!cgrp->parent || !((val == 0) || (val == 1)))
		return -EINVAL;

	parent = mem_cgroup_from_cont(cgrp->parent);

	cgroup_lock();
	/* oom-kill-disable is a flag for subhierarchy. */
	if ((parent->use_hierarchy) ||
	    (mem->use_hierarchy && !list_empty(&cgrp->children))) {
		cgroup_unlock();
		return -EINVAL;
	}
	mem->oom_kill_disable = val;
	if (!val)
		memcg_oom_recover(mem);
	cgroup_unlock();
	return 0;
}