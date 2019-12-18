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
struct task_struct {int flags; int /*<<< orphan*/  cg_list; struct css_set* cgroups; } ;
struct css_set {int /*<<< orphan*/  tasks; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cgroup {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CGROUP_SUBSYS_COUNT ; 
 int /*<<< orphan*/  CGRP_RELEASABLE ; 
 int ENOMEM ; 
 int ESRCH ; 
 int PF_EXITING ; 
 int /*<<< orphan*/  css_set_lock ; 
 struct css_set* find_css_set (struct css_set*,struct cgroup*) ; 
 struct css_set* find_existing_css_set (struct css_set*,struct cgroup*,struct cgroup_subsys_state**) ; 
 int /*<<< orphan*/  get_css_set (struct css_set*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  put_css_set (struct css_set*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct css_set*,struct css_set*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cgroup_task_migrate(struct cgroup *cgrp, struct cgroup *oldcgrp,
			       struct task_struct *tsk, bool guarantee)
{
	struct css_set *oldcg;
	struct css_set *newcg;

	/*
	 * get old css_set. we need to take task_lock and refcount it, because
	 * an exiting task can change its css_set to init_css_set and drop its
	 * old one without taking cgroup_mutex.
	 */
	task_lock(tsk);
	oldcg = tsk->cgroups;
	get_css_set(oldcg);
	task_unlock(tsk);

	/* locate or allocate a new css_set for this task. */
	if (guarantee) {
		/* we know the css_set we want already exists. */
		struct cgroup_subsys_state *template[CGROUP_SUBSYS_COUNT];
		read_lock(&css_set_lock);
		newcg = find_existing_css_set(oldcg, cgrp, template);
		BUG_ON(!newcg);
		get_css_set(newcg);
		read_unlock(&css_set_lock);
	} else {
		might_sleep();
		/* find_css_set will give us newcg already referenced. */
		newcg = find_css_set(oldcg, cgrp);
		if (!newcg) {
			put_css_set(oldcg);
			return -ENOMEM;
		}
	}
	put_css_set(oldcg);

	/* if PF_EXITING is set, the tsk->cgroups pointer is no longer safe. */
	task_lock(tsk);
	if (tsk->flags & PF_EXITING) {
		task_unlock(tsk);
		put_css_set(newcg);
		return -ESRCH;
	}
	rcu_assign_pointer(tsk->cgroups, newcg);
	task_unlock(tsk);

	/* Update the css_set linked lists if we're using them */
	write_lock(&css_set_lock);
	if (!list_empty(&tsk->cg_list))
		list_move(&tsk->cg_list, &newcg->tasks);
	write_unlock(&css_set_lock);

	/*
	 * We just gained a reference on oldcg by taking it from the task. As
	 * trading it for newcg is protected by cgroup_mutex, we're safe to drop
	 * it here; it will be freed under RCU.
	 */
	put_css_set(oldcg);

	set_bit(CGRP_RELEASABLE, &oldcgrp->flags);
	return 0;
}