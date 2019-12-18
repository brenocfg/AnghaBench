#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct wait_opts {int wo_flags; scalar_t__ wo_stat; scalar_t__ wo_rusage; int /*<<< orphan*/  wo_info; } ;
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
typedef  int pid_t ;
struct TYPE_6__ {int /*<<< orphan*/  uid; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CLD_CONTINUED ; 
 int /*<<< orphan*/  RUSAGE_BOTH ; 
 int /*<<< orphan*/  SIGCONT ; 
 int SIGNAL_STOP_CONTINUED ; 
 int WCONTINUED ; 
 int WNOWAIT ; 
 TYPE_3__* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int getrusage (struct task_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int put_user (int,scalar_t__) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int wait_noreap_copyout (struct wait_opts*,struct task_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_task_continued(struct wait_opts *wo, struct task_struct *p)
{
	int retval;
	pid_t pid;
	uid_t uid;

	if (!unlikely(wo->wo_flags & WCONTINUED))
		return 0;

	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED))
		return 0;

	spin_lock_irq(&p->sighand->siglock);
	/* Re-check with the lock held.  */
	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED)) {
		spin_unlock_irq(&p->sighand->siglock);
		return 0;
	}
	if (!unlikely(wo->wo_flags & WNOWAIT))
		p->signal->flags &= ~SIGNAL_STOP_CONTINUED;
	uid = __task_cred(p)->uid;
	spin_unlock_irq(&p->sighand->siglock);

	pid = task_pid_vnr(p);
	get_task_struct(p);
	read_unlock(&tasklist_lock);

	if (!wo->wo_info) {
		retval = wo->wo_rusage
			? getrusage(p, RUSAGE_BOTH, wo->wo_rusage) : 0;
		put_task_struct(p);
		if (!retval && wo->wo_stat)
			retval = put_user(0xffff, wo->wo_stat);
		if (!retval)
			retval = pid;
	} else {
		retval = wait_noreap_copyout(wo, p, pid, uid,
					     CLD_CONTINUED, SIGCONT);
		BUG_ON(retval == 0);
	}

	return retval;
}