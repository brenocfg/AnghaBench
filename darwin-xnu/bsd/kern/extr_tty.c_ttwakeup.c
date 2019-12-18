#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct tty {int /*<<< orphan*/  t_state; TYPE_1__ t_rsel; } ;

/* Variables and functions */
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  TSA_HUP_OR_INPUT (struct tty*) ; 
 int /*<<< orphan*/  TS_ASYNC ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_pgsignal (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
ttwakeup(struct tty *tp)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	selwakeup(&tp->t_rsel);
	KNOTE(&tp->t_rsel.si_note, 1);
	if (ISSET(tp->t_state, TS_ASYNC)) {
		/*
		 * XXX: Callers may not revalidate it the tty is closed
		 * XXX: out from under them by another thread, but we do
		 * XXX: not support queued signals.  This should be safe,
		 * XXX: since the process we intend to wakeup is in the
		 * XXX: process group, and will wake up because of the
		 * XXX: signal anyway.
		 */
		tty_unlock(tp);
		tty_pgsignal(tp, SIGIO, 1);
		tty_lock(tp);
	}
	wakeup(TSA_HUP_OR_INPUT(tp));
}