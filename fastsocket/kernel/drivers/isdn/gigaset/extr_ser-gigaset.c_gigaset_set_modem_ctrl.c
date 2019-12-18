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
struct tty_struct {TYPE_3__* ops; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* ser; } ;
struct cardstate {TYPE_2__ hw; } ;
struct TYPE_6__ {int (* tiocmset ) (struct tty_struct*,int /*<<< orphan*/ *,unsigned int,unsigned int) ;} ;
struct TYPE_4__ {struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IF ; 
 int EINVAL ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int gigaset_set_modem_ctrl(struct cardstate *cs, unsigned old_state, unsigned new_state)
{
	struct tty_struct *tty = cs->hw.ser->tty;
	unsigned int set, clear;

	if (!tty || !tty->driver || !tty->ops->tiocmset)
		return -EINVAL;
	set = new_state & ~old_state;
	clear = old_state & ~new_state;
	if (!set && !clear)
		return 0;
	gig_dbg(DEBUG_IF, "tiocmset set %x clear %x", set, clear);
	return tty->ops->tiocmset(tty, NULL, set, clear);
}