#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {TYPE_1__* sighand; TYPE_2__* signal; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  audit_tty; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  tty_audit_push_task (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_prepare_user_tty(pid_t pid, uid_t loginuid, u32 sessionid)
{
	struct task_struct *tsk;
	int err;

	read_lock(&tasklist_lock);
	tsk = find_task_by_vpid(pid);
	err = -ESRCH;
	if (!tsk)
		goto out;
	err = 0;

	spin_lock_irq(&tsk->sighand->siglock);
	if (!tsk->signal->audit_tty)
		err = -EPERM;
	spin_unlock_irq(&tsk->sighand->siglock);
	if (err)
		goto out;

	tty_audit_push_task(tsk, loginuid, sessionid);
out:
	read_unlock(&tasklist_lock);
	return err;
}