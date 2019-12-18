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
struct task_struct {struct io_context* io_context; } ;
struct io_context {int ioprio; int ioprio_changed; } ;
struct cred {scalar_t__ uid; scalar_t__ euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct cred* __task_cred (struct task_struct*) ; 
 struct io_context* alloc_io_context (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_task_setioprio (struct task_struct*,int) ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

int set_task_ioprio(struct task_struct *task, int ioprio)
{
	int err;
	struct io_context *ioc;
	const struct cred *cred = current_cred(), *tcred;

	rcu_read_lock();
	tcred = __task_cred(task);
	if (tcred->uid != cred->euid &&
	    tcred->uid != cred->uid && !capable(CAP_SYS_NICE)) {
		rcu_read_unlock();
		return -EPERM;
	}
	rcu_read_unlock();

	err = security_task_setioprio(task, ioprio);
	if (err)
		return err;

	task_lock(task);
	do {
		ioc = task->io_context;
		/* see wmb() in current_io_context() */
		smp_read_barrier_depends();
		if (ioc)
			break;

		ioc = alloc_io_context(GFP_ATOMIC, -1);
		if (!ioc) {
			err = -ENOMEM;
			break;
		}
		task->io_context = ioc;
	} while (1);

	if (!err) {
		ioc->ioprio = ioprio;
		ioc->ioprio_changed = 1;
	}

	task_unlock(task);
	return err;
}