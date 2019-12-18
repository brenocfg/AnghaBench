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
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct tty_struct {int /*<<< orphan*/  ldisc_mutex; TYPE_3__ buf; TYPE_2__* ops; struct tty_ldisc* ldisc; int /*<<< orphan*/  flags; scalar_t__ receive_room; struct tty_struct* link; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_ldisc ) (struct tty_struct*) ;} ;
struct TYPE_4__ {int num; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int PTR_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  TTY_HUPPED ; 
 int /*<<< orphan*/  TTY_LDISC_CHANGING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_assign (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_enable (struct tty_struct*) ; 
 struct tty_ldisc* tty_ldisc_get (int) ; 
 int tty_ldisc_halt (struct tty_struct*) ; 
 int tty_ldisc_open (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_put (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_restore (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_wait ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int tty_set_ldisc(struct tty_struct *tty, int ldisc)
{
	int retval;
	struct tty_ldisc *o_ldisc, *new_ldisc;
	int work, o_work = 0;
	struct tty_struct *o_tty;

	new_ldisc = tty_ldisc_get(ldisc);
	if (IS_ERR(new_ldisc))
		return PTR_ERR(new_ldisc);

	/*
	 *	We need to look at the tty locking here for pty/tty pairs
	 *	when both sides try to change in parallel.
	 */

	o_tty = tty->link;	/* o_tty is the pty side or NULL */


	/*
	 *	Check the no-op case
	 */

	if (tty->ldisc->ops->num == ldisc) {
		tty_ldisc_put(new_ldisc);
		return 0;
	}

	/*
	 *	Problem: What do we do if this blocks ?
	 *	We could deadlock here
	 */

	tty_wait_until_sent(tty, 0);

	mutex_lock(&tty->ldisc_mutex);

	/*
	 *	We could be midstream of another ldisc change which has
	 *	dropped the lock during processing. If so we need to wait.
	 */

	while (test_bit(TTY_LDISC_CHANGING, &tty->flags)) {
		mutex_unlock(&tty->ldisc_mutex);
		wait_event(tty_ldisc_wait,
			test_bit(TTY_LDISC_CHANGING, &tty->flags) == 0);
		mutex_lock(&tty->ldisc_mutex);
	}
	set_bit(TTY_LDISC_CHANGING, &tty->flags);

	/*
	 *	No more input please, we are switching. The new ldisc
	 *	will update this value in the ldisc open function
	 */

	tty->receive_room = 0;

	o_ldisc = tty->ldisc;
	/*
	 *	Make sure we don't change while someone holds a
	 *	reference to the line discipline. The TTY_LDISC bit
	 *	prevents anyone taking a reference once it is clear.
	 *	We need the lock to avoid racing reference takers.
	 *
	 *	We must clear the TTY_LDISC bit here to avoid a livelock
	 *	with a userspace app continually trying to use the tty in
	 *	parallel to the change and re-referencing the tty.
	 */

	work = tty_ldisc_halt(tty);
	if (o_tty)
		o_work = tty_ldisc_halt(o_tty);

	/*
	 * Wait for ->hangup_work and ->buf.work handlers to terminate.
	 * We must drop the mutex here in case a hangup is also in process.
	 */

	mutex_unlock(&tty->ldisc_mutex);

	flush_scheduled_work();

	mutex_lock(&tty->ldisc_mutex);
	if (test_bit(TTY_HUPPED, &tty->flags)) {
		/* We were raced by the hangup method. It will have stomped
		   the ldisc data and closed the ldisc down */
		clear_bit(TTY_LDISC_CHANGING, &tty->flags);
		mutex_unlock(&tty->ldisc_mutex);
		tty_ldisc_put(new_ldisc);
		return -EIO;
	}

	/* Shutdown the current discipline. */
	tty_ldisc_close(tty, o_ldisc);

	/* Now set up the new line discipline. */
	tty_ldisc_assign(tty, new_ldisc);
	tty_set_termios_ldisc(tty, ldisc);

	retval = tty_ldisc_open(tty, new_ldisc);
	if (retval < 0) {
		/* Back to the old one or N_TTY if we can't */
		tty_ldisc_put(new_ldisc);
		tty_ldisc_restore(tty, o_ldisc);
	}

	/* At this point we hold a reference to the new ldisc and a
	   a reference to the old ldisc. If we ended up flipping back
	   to the existing ldisc we have two references to it */

	if (tty->ldisc->ops->num != o_ldisc->ops->num && tty->ops->set_ldisc)
		tty->ops->set_ldisc(tty);

	tty_ldisc_put(o_ldisc);

	/*
	 *	Allow ldisc referencing to occur again
	 */

	tty_ldisc_enable(tty);
	if (o_tty)
		tty_ldisc_enable(o_tty);

	/* Restart the work queue in case no characters kick it off. Safe if
	   already running */
	if (work)
		schedule_delayed_work(&tty->buf.work, 1);
	if (o_work)
		schedule_delayed_work(&o_tty->buf.work, 1);
	mutex_unlock(&tty->ldisc_mutex);
	return retval;
}