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
struct tty_struct {int /*<<< orphan*/  ldisc_mutex; scalar_t__ ldisc; TYPE_3__* termios; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  flags; TYPE_1__* driver; } ;
struct tty_ldisc {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  c_line; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hangup ) (struct tty_struct*) ;int /*<<< orphan*/  (* write_wakeup ) (struct tty_struct*) ;int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_TTY ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int TTY_DRIVER_RESET_TERMIOS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub3 (struct tty_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_enable (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_halt (struct tty_struct*) ; 
 int tty_ldisc_open (struct tty_struct*,scalar_t__) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_reinit (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_reset_termios (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_ldisc_hangup(struct tty_struct *tty)
{
	struct tty_ldisc *ld;
	int reset = tty->driver->flags & TTY_DRIVER_RESET_TERMIOS;
	int err = 0;

	/*
	 * FIXME! What are the locking issues here? This may me overdoing
	 * things... This question is especially important now that we've
	 * removed the irqlock.
	 */
	ld = tty_ldisc_ref(tty);
	if (ld != NULL) {
		/* We may have no line discipline at this point */
		if (ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		tty_driver_flush_buffer(tty);
		if ((test_bit(TTY_DO_WRITE_WAKEUP, &tty->flags)) &&
		    ld->ops->write_wakeup)
			ld->ops->write_wakeup(tty);
		if (ld->ops->hangup)
			ld->ops->hangup(tty);
		tty_ldisc_deref(ld);
	}
	/*
	 * FIXME: Once we trust the LDISC code better we can wait here for
	 * ldisc completion and fix the driver call race
	 */
	wake_up_interruptible_poll(&tty->write_wait, POLLOUT);
	wake_up_interruptible_poll(&tty->read_wait, POLLIN);
	/*
	 * Shutdown the current line discipline, and reset it to
	 * N_TTY if need be.
	 *
	 * Avoid racing set_ldisc or tty_ldisc_release
	 */
	mutex_lock(&tty->ldisc_mutex);
	tty_ldisc_halt(tty);
	/* At this point we have a closed ldisc and we want to
	   reopen it. We could defer this to the next open but
	   it means auditing a lot of other paths so this is
	   a FIXME */
	if (tty->ldisc) {	/* Not yet closed */
		if (reset == 0) {

			if (!tty_ldisc_reinit(tty, tty->termios->c_line))
				err = tty_ldisc_open(tty, tty->ldisc);
			else
				err = 1;
		}
		/* If the re-open fails or we reset then go to N_TTY. The
		   N_TTY open cannot fail */
		if (reset || err) {
			BUG_ON(tty_ldisc_reinit(tty, N_TTY));
			WARN_ON(tty_ldisc_open(tty, tty->ldisc));
		}
		tty_ldisc_enable(tty);
	}
	mutex_unlock(&tty->ldisc_mutex);
	if (reset)
		tty_reset_termios(tty);
}