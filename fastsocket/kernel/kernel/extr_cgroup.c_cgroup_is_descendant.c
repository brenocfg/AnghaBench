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
struct task_struct {int dummy; } ;
typedef  struct cgroup {struct cgroup const* parent; struct cgroup const* top_cgroup; int /*<<< orphan*/  root; } const cgroup ;

/* Variables and functions */
 struct cgroup const* dummytop ; 
 struct cgroup const* task_cgroup_from_root (struct task_struct*,int /*<<< orphan*/ ) ; 

int cgroup_is_descendant(const struct cgroup *cgrp, struct task_struct *task)
{
	int ret;
	struct cgroup *target;

	if (cgrp == dummytop)
		return 1;

	target = task_cgroup_from_root(task, cgrp->root);
	while (cgrp != target && cgrp!= cgrp->top_cgroup)
		cgrp = cgrp->parent;
	ret = (cgrp == target);
	return ret;
}