#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct task_security_struct {scalar_t__ osid; scalar_t__ sid; } ;
struct linux_binprm {int dummy; } ;
struct itimerval {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  real_parent; TYPE_2__* sighand; int /*<<< orphan*/  blocked; TYPE_1__* signal; } ;
struct TYPE_8__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS__SIGINH ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int SIGNAL_GROUP_EXIT ; 
 int /*<<< orphan*/  __flush_signals (TYPE_3__*) ; 
 int /*<<< orphan*/  __wake_up_parent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int avc_has_perm (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 struct task_security_struct* current_security () ; 
 int /*<<< orphan*/  do_setitimer (int,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_signal_handlers (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 

__attribute__((used)) static void selinux_bprm_committed_creds(struct linux_binprm *bprm)
{
	const struct task_security_struct *tsec = current_security();
	struct itimerval itimer;
	u32 osid, sid;
	int rc, i;

	osid = tsec->osid;
	sid = tsec->sid;

	if (sid == osid)
		return;

	/* Check whether the new SID can inherit signal state from the old SID.
	 * If not, clear itimers to avoid subsequent signal generation and
	 * flush and unblock signals.
	 *
	 * This must occur _after_ the task SID has been updated so that any
	 * kill done after the flush will be checked against the new SID.
	 */
	rc = avc_has_perm(osid, sid, SECCLASS_PROCESS, PROCESS__SIGINH, NULL);
	if (rc) {
		memset(&itimer, 0, sizeof itimer);
		for (i = 0; i < 3; i++)
			do_setitimer(i, &itimer, NULL);
		spin_lock_irq(&current->sighand->siglock);
		if (!(current->signal->flags & SIGNAL_GROUP_EXIT)) {
			__flush_signals(current);
			flush_signal_handlers(current, 1);
			sigemptyset(&current->blocked);
		}
		spin_unlock_irq(&current->sighand->siglock);
	}

	/* Wake up the parent if it is waiting so that it can recheck
	 * wait permission to the new task SID. */
	read_lock(&tasklist_lock);
	__wake_up_parent(current, current->real_parent);
	read_unlock(&tasklist_lock);
}