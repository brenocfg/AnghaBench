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
struct tty_struct {int /*<<< orphan*/  icanon; scalar_t__ index; TYPE_1__* driver; } ;
struct tty_audit_buf {int /*<<< orphan*/  count; } ;
struct TYPE_8__ {TYPE_3__* sighand; TYPE_2__* signal; } ;
struct TYPE_7__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_6__ {struct tty_audit_buf* tty_audit_buf; int /*<<< orphan*/  audit_tty; } ;
struct TYPE_5__ {scalar_t__ minor_start; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 TYPE_4__* current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct tty_audit_buf* tty_audit_buf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_audit_buf_free (struct tty_audit_buf*) ; 

__attribute__((used)) static struct tty_audit_buf *tty_audit_buf_get(struct tty_struct *tty)
{
	struct tty_audit_buf *buf, *buf2;

	buf = NULL;
	buf2 = NULL;
	spin_lock_irq(&current->sighand->siglock);
	if (likely(!current->signal->audit_tty))
		goto out;
	buf = current->signal->tty_audit_buf;
	if (buf) {
		atomic_inc(&buf->count);
		goto out;
	}
	spin_unlock_irq(&current->sighand->siglock);

	buf2 = tty_audit_buf_alloc(tty->driver->major,
				   tty->driver->minor_start + tty->index,
				   tty->icanon);
	if (buf2 == NULL) {
		audit_log_lost("out of memory in TTY auditing");
		return NULL;
	}

	spin_lock_irq(&current->sighand->siglock);
	if (!current->signal->audit_tty)
		goto out;
	buf = current->signal->tty_audit_buf;
	if (!buf) {
		current->signal->tty_audit_buf = buf2;
		buf = buf2;
		buf2 = NULL;
	}
	atomic_inc(&buf->count);
	/* Fall through */
 out:
	spin_unlock_irq(&current->sighand->siglock);
	if (buf2)
		tty_audit_buf_free(buf2);
	return buf;
}