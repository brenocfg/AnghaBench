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
struct tty_ldisc_ops {int num; scalar_t__ refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int NR_LDISCS ; 
 int N_TTY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_ldisc_lock ; 
 struct tty_ldisc_ops** tty_ldiscs ; 

int tty_register_ldisc(int disc, struct tty_ldisc_ops *new_ldisc)
{
	unsigned long flags;
	int ret = 0;

	if (disc < N_TTY || disc >= NR_LDISCS)
		return -EINVAL;

	spin_lock_irqsave(&tty_ldisc_lock, flags);
	tty_ldiscs[disc] = new_ldisc;
	new_ldisc->num = disc;
	new_ldisc->refcount = 0;
	spin_unlock_irqrestore(&tty_ldisc_lock, flags);

	return ret;
}