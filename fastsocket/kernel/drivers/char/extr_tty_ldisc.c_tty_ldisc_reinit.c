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
struct tty_struct {int /*<<< orphan*/ * ldisc; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_assign (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,int /*<<< orphan*/ *) ; 
 struct tty_ldisc* tty_ldisc_get (int) ; 
 int /*<<< orphan*/  tty_ldisc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int) ; 

__attribute__((used)) static int tty_ldisc_reinit(struct tty_struct *tty, int ldisc)
{
	struct tty_ldisc *ld = tty_ldisc_get(ldisc);

	if (IS_ERR(ld))
		return -1;

	tty_ldisc_close(tty, tty->ldisc);
	tty_ldisc_put(tty->ldisc);
	tty->ldisc = NULL;
	/*
	 *	Switch the line discipline back
	 */
	tty_ldisc_assign(tty, ld);
	tty_set_termios_ldisc(tty, ldisc);

	return 0;
}