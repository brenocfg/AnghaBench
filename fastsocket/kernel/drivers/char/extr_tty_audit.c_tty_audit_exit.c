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
struct tty_audit_buf {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {struct tty_audit_buf* tty_audit_buf; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_push_current (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_put (struct tty_audit_buf*) ; 

void tty_audit_exit(void)
{
	struct tty_audit_buf *buf;

	spin_lock_irq(&current->sighand->siglock);
	buf = current->signal->tty_audit_buf;
	current->signal->tty_audit_buf = NULL;
	spin_unlock_irq(&current->sighand->siglock);
	if (!buf)
		return;

	mutex_lock(&buf->mutex);
	tty_audit_buf_push_current(buf);
	mutex_unlock(&buf->mutex);

	tty_audit_buf_put(buf);
}