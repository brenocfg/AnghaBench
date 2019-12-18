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
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct asyncppp {int /*<<< orphan*/  tsk; int /*<<< orphan*/  xmit_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  XMIT_WAKEUP ; 
 struct asyncppp* ap_get (struct tty_struct*) ; 
 int /*<<< orphan*/  ap_put (struct asyncppp*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ppp_asynctty_wakeup(struct tty_struct *tty)
{
	struct asyncppp *ap = ap_get(tty);

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	if (!ap)
		return;
	set_bit(XMIT_WAKEUP, &ap->xmit_flags);
	tasklet_schedule(&ap->tsk);
	ap_put(ap);
}