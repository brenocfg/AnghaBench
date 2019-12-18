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
struct ipath_devdata {unsigned int ipath_sendctrl; int /*<<< orphan*/  ipath_sendctrl_lock; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_scratch; int /*<<< orphan*/  kr_sendctrl; } ;

/* Variables and functions */
 unsigned int INFINIPATH_S_DISARM ; 
 unsigned int INFINIPATH_S_DISARMPIOBUF_SHIFT ; 
 int /*<<< orphan*/  PKT ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ipath_force_pio_avail_update (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipath_disarm_piobufs(struct ipath_devdata *dd, unsigned first,
			  unsigned cnt)
{
	unsigned i, last = first + cnt;
	unsigned long flags;

	ipath_cdbg(PKT, "disarm %u PIObufs first=%u\n", cnt, first);
	for (i = first; i < last; i++) {
		spin_lock_irqsave(&dd->ipath_sendctrl_lock, flags);
		/*
		 * The disarm-related bits are write-only, so it
		 * is ok to OR them in with our copy of sendctrl
		 * while we hold the lock.
		 */
		ipath_write_kreg(dd, dd->ipath_kregs->kr_sendctrl,
			dd->ipath_sendctrl | INFINIPATH_S_DISARM |
			(i << INFINIPATH_S_DISARMPIOBUF_SHIFT));
		/* can't disarm bufs back-to-back per iba7220 spec */
		ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
		spin_unlock_irqrestore(&dd->ipath_sendctrl_lock, flags);
	}
	/* on some older chips, update may not happen after cancel */
	ipath_force_pio_avail_update(dd);
}