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
struct TYPE_2__ {scalar_t__ refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NR_LDISCS ; 
 int N_TTY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_ldisc_lock ; 
 TYPE_1__** tty_ldiscs ; 

int tty_unregister_ldisc(int disc)
{
	unsigned long flags;
	int ret = 0;

	if (disc < N_TTY || disc >= NR_LDISCS)
		return -EINVAL;

	spin_lock_irqsave(&tty_ldisc_lock, flags);
	if (tty_ldiscs[disc]->refcount)
		ret = -EBUSY;
	else
		tty_ldiscs[disc] = NULL;
	spin_unlock_irqrestore(&tty_ldisc_lock, flags);

	return ret;
}