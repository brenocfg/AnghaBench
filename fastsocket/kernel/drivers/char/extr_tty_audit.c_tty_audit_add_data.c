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
struct tty_struct {scalar_t__ icanon; int index; TYPE_3__* driver; } ;
struct tty_audit_buf {int major; int minor; scalar_t__ icanon; scalar_t__ valid; scalar_t__ data; int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ subtype; int major; int minor_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_5__ {int audit_tty_log_passwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_ECHO (struct tty_struct*) ; 
 scalar_t__ N_TTY_BUF_SIZE ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tty_audit_buf* tty_audit_buf_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_audit_buf_push_current (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_put (struct tty_audit_buf*) ; 
 scalar_t__ unlikely (int) ; 

void tty_audit_add_data(struct tty_struct *tty, unsigned char *data,
			size_t size)
{
	struct tty_audit_buf *buf;
	int major, minor;
	int audit_log_tty_passwd;
	unsigned long flags;

	if (unlikely(size == 0))
		return;

	spin_lock_irqsave(&current->sighand->siglock, flags);
	audit_log_tty_passwd = current->signal->audit_tty_log_passwd;
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
	if (!audit_log_tty_passwd && tty->icanon && !L_ECHO(tty))
		return;

	if (tty->driver->type == TTY_DRIVER_TYPE_PTY
	    && tty->driver->subtype == PTY_TYPE_MASTER)
		return;

	buf = tty_audit_buf_get(tty);
	if (!buf)
		return;

	mutex_lock(&buf->mutex);
	major = tty->driver->major;
	minor = tty->driver->minor_start + tty->index;
	if (buf->major != major || buf->minor != minor
	    || buf->icanon != tty->icanon) {
		tty_audit_buf_push_current(buf);
		buf->major = major;
		buf->minor = minor;
		buf->icanon = tty->icanon;
	}
	do {
		size_t run;

		run = N_TTY_BUF_SIZE - buf->valid;
		if (run > size)
			run = size;
		memcpy(buf->data + buf->valid, data, run);
		buf->valid += run;
		data += run;
		size -= run;
		if (buf->valid == N_TTY_BUF_SIZE)
			tty_audit_buf_push_current(buf);
	} while (size != 0);
	mutex_unlock(&buf->mutex);
	tty_audit_buf_put(buf);
}