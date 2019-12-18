#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  ldisc_mutex; int /*<<< orphan*/ * ldisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_TTY ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_halt (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int /*<<< orphan*/ ) ; 

void tty_ldisc_release(struct tty_struct *tty, struct tty_struct *o_tty)
{
	/*
	 * Prevent flush_to_ldisc() from rescheduling the work for later.  Then
	 * kill any delayed work. As this is the final close it does not
	 * race with the set_ldisc code path.
	 */

	tty_ldisc_halt(tty);
	flush_scheduled_work();

	mutex_lock(&tty->ldisc_mutex);
	/*
	 * Now kill off the ldisc
	 */
	tty_ldisc_close(tty, tty->ldisc);
	tty_ldisc_put(tty->ldisc);
	/* Force an oops if we mess this up */
	tty->ldisc = NULL;

	/* Ensure the next open requests the N_TTY ldisc */
	tty_set_termios_ldisc(tty, N_TTY);
	mutex_unlock(&tty->ldisc_mutex);

	/* This will need doing differently if we need to lock */
	if (o_tty)
		tty_ldisc_release(o_tty, NULL);

	/* And the memory resources remaining (buffers, termios) will be
	   disposed of when the kref hits zero */
}