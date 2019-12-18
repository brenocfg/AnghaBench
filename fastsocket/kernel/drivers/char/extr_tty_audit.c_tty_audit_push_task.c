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
struct tty_audit_buf {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;
struct task_struct {TYPE_1__* sighand; TYPE_2__* signal; } ;
struct TYPE_4__ {struct tty_audit_buf* tty_audit_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_push (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_put (struct tty_audit_buf*) ; 

void tty_audit_push_task(struct task_struct *tsk, uid_t loginuid, u32 sessionid)
{
	struct tty_audit_buf *buf;

	spin_lock_irq(&tsk->sighand->siglock);
	buf = tsk->signal->tty_audit_buf;
	if (buf)
		atomic_inc(&buf->count);
	spin_unlock_irq(&tsk->sighand->siglock);
	if (!buf)
		return;

	mutex_lock(&buf->mutex);
	tty_audit_buf_push(tsk, loginuid, sessionid, buf);
	mutex_unlock(&buf->mutex);

	tty_audit_buf_put(buf);
}