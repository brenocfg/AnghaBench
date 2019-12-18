#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; TYPE_3__* driver; } ;
struct tty_audit_buf {int major; int minor; int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;
struct TYPE_8__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_7__ {int major; int minor_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_5__ {struct tty_audit_buf* tty_audit_buf; int /*<<< orphan*/  audit_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_push_current (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_put (struct tty_audit_buf*) ; 

void tty_audit_push(struct tty_struct *tty)
{
	struct tty_audit_buf *buf;

	spin_lock_irq(&current->sighand->siglock);
	if (likely(!current->signal->audit_tty)) {
		spin_unlock_irq(&current->sighand->siglock);
		return;
	}
	buf = current->signal->tty_audit_buf;
	if (buf)
		atomic_inc(&buf->count);
	spin_unlock_irq(&current->sighand->siglock);

	if (buf) {
		int major, minor;

		major = tty->driver->major;
		minor = tty->driver->minor_start + tty->index;
		mutex_lock(&buf->mutex);
		if (buf->major == major && buf->minor == minor)
			tty_audit_buf_push_current(buf);
		mutex_unlock(&buf->mutex);
		tty_audit_buf_put(buf);
	}
}