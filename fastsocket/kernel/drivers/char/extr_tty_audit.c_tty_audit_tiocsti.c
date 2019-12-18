#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct tty_struct {int index; TYPE_3__* driver; } ;
struct tty_audit_buf {int major; int minor; int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;
struct TYPE_11__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_10__ {int major; int minor_start; } ;
struct TYPE_9__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_8__ {int audit_tty; struct tty_audit_buf* tty_audit_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  audit_get_loginuid (TYPE_4__*) ; 
 unsigned int audit_get_sessionid (TYPE_4__*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_push_current (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_put (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_log (char*,TYPE_4__*,int /*<<< orphan*/ ,unsigned int,int,int,char*,int) ; 

void tty_audit_tiocsti(struct tty_struct *tty, char ch)
{
	struct tty_audit_buf *buf;
	int major, minor, should_audit;

	spin_lock_irq(&current->sighand->siglock);
	should_audit = current->signal->audit_tty;
	buf = current->signal->tty_audit_buf;
	if (buf)
		atomic_inc(&buf->count);
	spin_unlock_irq(&current->sighand->siglock);

	major = tty->driver->major;
	minor = tty->driver->minor_start + tty->index;
	if (buf) {
		mutex_lock(&buf->mutex);
		if (buf->major == major && buf->minor == minor)
			tty_audit_buf_push_current(buf);
		mutex_unlock(&buf->mutex);
		tty_audit_buf_put(buf);
	}

	if (should_audit && audit_enabled) {
		uid_t auid;
		unsigned int sessionid;

		auid = audit_get_loginuid(current);
		sessionid = audit_get_sessionid(current);
		tty_audit_log("ioctl=TIOCSTI", current, auid, sessionid, major,
			      minor, &ch, 1);
	}
}