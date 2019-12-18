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
typedef  scalar_t__ u64 ;
struct task_struct {int flags; struct task_struct* group_leader; } ;
struct cred {scalar_t__ euid; scalar_t__ uid; scalar_t__ suid; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int ESRCH ; 
 int PF_EXITING ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int cgroup_attach_proc (struct cgroup*,struct task_struct*) ; 
 int cgroup_attach_task (struct cgroup*,struct task_struct*) ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 struct task_struct* current ; 
 struct cred* current_cred () ; 
 struct task_struct* find_task_by_vpid (scalar_t__) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  threadgroup_fork_write_lock (struct task_struct*) ; 
 int /*<<< orphan*/  threadgroup_fork_write_unlock (struct task_struct*) ; 

__attribute__((used)) static int attach_task_by_pid(struct cgroup *cgrp, u64 pid, bool threadgroup)
{
	struct task_struct *tsk;
	const struct cred *cred = current_cred(), *tcred;
	int ret;

	if (!cgroup_lock_live_group(cgrp))
		return -ENODEV;

	if (pid) {
		rcu_read_lock();
		tsk = find_task_by_vpid(pid);
		if (!tsk) {
			rcu_read_unlock();
			cgroup_unlock();
			return -ESRCH;
		}
		if (threadgroup) {
			/*
			 * RCU protects this access, since tsk was found in the
			 * tid map. a race with de_thread may cause group_leader
			 * to stop being the leader, but cgroup_attach_proc will
			 * detect it later.
			 */
			tsk = tsk->group_leader;
		} else if (tsk->flags & PF_EXITING) {
			/* optimization for the single-task-only case */
			rcu_read_unlock();
			cgroup_unlock();
			return -ESRCH;
		}

		/*
		 * even if we're attaching all tasks in the thread group, we
		 * only need to check permissions on one of them.
		 */
		tcred = __task_cred(tsk);
		if (cred->euid &&
		    cred->euid != tcred->uid &&
		    cred->euid != tcred->suid) {
			rcu_read_unlock();
			cgroup_unlock();
			return -EACCES;
		}
		get_task_struct(tsk);
		rcu_read_unlock();
	} else {
		if (threadgroup)
			tsk = current->group_leader;
		else
			tsk = current;
		get_task_struct(tsk);
	}

	if (threadgroup) {
		threadgroup_fork_write_lock(tsk);
		ret = cgroup_attach_proc(cgrp, tsk);
		threadgroup_fork_write_unlock(tsk);
	} else {
		ret = cgroup_attach_task(cgrp, tsk);
	}
	put_task_struct(tsk);
	cgroup_unlock();
	return ret;
}