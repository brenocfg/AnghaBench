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
struct tty_struct {int dummy; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  N_TTY ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tty_ldisc_assign (struct tty_struct*,struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_get (int /*<<< orphan*/ ) ; 

void tty_ldisc_init(struct tty_struct *tty)
{
	struct tty_ldisc *ld = tty_ldisc_get(N_TTY);
	if (IS_ERR(ld))
		panic("n_tty: init_tty");
	tty_ldisc_assign(tty, ld);
}