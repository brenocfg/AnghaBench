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
struct task_struct {struct css_set* cgroups; int /*<<< orphan*/  cg_list; } ;
struct css_set {int /*<<< orphan*/ * subsys; } ;
struct cgroup_subsys {int /*<<< orphan*/  (* exit ) (struct cgroup_subsys*,struct cgroup*,struct cgroup*,struct task_struct*) ;} ;
struct cgroup {int dummy; } ;
struct TYPE_2__ {struct cgroup* cgroup; } ;

/* Variables and functions */
 int CGROUP_SUBSYS_COUNT ; 
 int /*<<< orphan*/  css_set_lock ; 
 struct css_set init_css_set ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ need_forkexit_callback ; 
 int /*<<< orphan*/  put_css_set_taskexit (struct css_set*) ; 
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cgroup_subsys*,struct cgroup*,struct cgroup*,struct task_struct*) ; 
 struct cgroup_subsys** subsys ; 
 struct cgroup* task_cgroup (struct task_struct*,int) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void cgroup_exit(struct task_struct *tsk, int run_callbacks)
{
	int i;
	struct css_set *cg;


	/*
	 * Unlink from the css_set task list if necessary.
	 * Optimistically check cg_list before taking
	 * css_set_lock
	 */
	if (!list_empty(&tsk->cg_list)) {
		write_lock(&css_set_lock);
		if (!list_empty(&tsk->cg_list))
			list_del(&tsk->cg_list);
		write_unlock(&css_set_lock);
	}

	/* Reassign the task to the init_css_set. */
	task_lock(tsk);
	cg = tsk->cgroups;
	tsk->cgroups = &init_css_set;

	if (run_callbacks && need_forkexit_callback) {
		/*
		 * modular subsystems can't use callbacks, so no need to lock
		 * the subsys array
		 */
		for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
			struct cgroup_subsys *ss = subsys[i];
			if (ss->exit) {
				struct cgroup *old_cgrp =
					rcu_dereference(cg->subsys[i])->cgroup;
				struct cgroup *cgrp = task_cgroup(tsk, i);
				ss->exit(ss, cgrp, old_cgrp, tsk);
			}
		}
	}
	task_unlock(tsk);

	if (cg)
		put_css_set_taskexit(cg);
}