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
struct task_struct {int /*<<< orphan*/  group_leader; TYPE_1__* signal; int /*<<< orphan*/  sighand; } ;
struct rlimit {int rlim_cur; int rlim_max; } ;
struct TYPE_2__ {struct rlimit* rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 unsigned int RLIMIT_CPU ; 
 unsigned int RLIMIT_NOFILE ; 
 int RLIM_INFINITY ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int security_task_setrlimit (struct task_struct*,unsigned int,struct rlimit*) ; 
 scalar_t__ sysctl_nr_open ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  update_rlimit_cpu (struct task_struct*,int) ; 

int setrlimit(struct task_struct *tsk, unsigned int resource,
		struct rlimit *new_rlim)
{
	struct rlimit *old_rlim;
	int retval;

	if (new_rlim->rlim_cur > new_rlim->rlim_max)
		return -EINVAL;
	if (resource == RLIMIT_NOFILE && new_rlim->rlim_max > sysctl_nr_open)
		return -EPERM;

	/* optimization: 'current' doesn't need locking, e.g. setrlimit */
	if (tsk != current) {
		/* protect tsk->signal and tsk->sighand from disappearing */
		read_lock(&tasklist_lock);
		if (!tsk->sighand) {
			retval = -ESRCH;
			goto out;
		}
	}

	retval = security_task_setrlimit(tsk, resource, new_rlim);
	if (retval)
		goto out;

	if (resource == RLIMIT_CPU && new_rlim->rlim_cur == 0) {
		/*
		 * The caller is asking for an immediate RLIMIT_CPU
		 * expiry.  But we use the zero value to mean "it was
		 * never set".  So let's cheat and make it one second
		 * instead
		 */
		new_rlim->rlim_cur = 1;
	}

	old_rlim = tsk->signal->rlim + resource;
	task_lock(tsk->group_leader);
	if ((new_rlim->rlim_max <= old_rlim->rlim_max) ||
				capable(CAP_SYS_RESOURCE))
		*old_rlim = *new_rlim;
	else
		retval = -EPERM;
	task_unlock(tsk->group_leader);

	if (retval || resource != RLIMIT_CPU)
		goto out;

	/*
	 * RLIMIT_CPU handling.   Note that the kernel fails to return an error
	 * code if it rejected the user's attempt to set RLIMIT_CPU.  This is a
	 * very long-standing error, and fixing it now risks breakage of
	 * applications, so we live with it
	 */
	if (new_rlim->rlim_cur == RLIM_INFINITY)
		goto out;

	update_rlimit_cpu(tsk, new_rlim->rlim_cur);
out:
	if (tsk != current)
		read_unlock(&tasklist_lock);
	return retval;
}