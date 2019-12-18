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
struct tty_struct {int /*<<< orphan*/  write_wait; int /*<<< orphan*/  flags; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_wakeup ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_wakeup(struct tty_struct *tty)
{
	struct tty_ldisc *ld;

	if (test_bit(TTY_DO_WRITE_WAKEUP, &tty->flags)) {
		ld = tty_ldisc_ref(tty);
		if (ld) {
			if (ld->ops->write_wakeup)
				ld->ops->write_wakeup(tty);
			tty_ldisc_deref(ld);
		}
	}
	wake_up_interruptible_poll(&tty->write_wait, POLLOUT);
}