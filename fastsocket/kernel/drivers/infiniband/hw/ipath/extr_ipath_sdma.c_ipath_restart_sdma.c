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
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/  verbs_dev; int /*<<< orphan*/  ipath_sendctrl_lock; TYPE_1__* ipath_kregs; int /*<<< orphan*/  ipath_sendctrl; int /*<<< orphan*/  ipath_sdma_status; int /*<<< orphan*/  ipath_sdma_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_scratch; int /*<<< orphan*/  kr_sendctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIPATH_S_SDMAENABLE ; 
 int IPATH_HAS_SEND_DMA ; 
 int /*<<< orphan*/  IPATH_SDMA_ABORTING ; 
 int /*<<< orphan*/  IPATH_SDMA_DISABLED ; 
 int /*<<< orphan*/  IPATH_SDMA_DISARMED ; 
 int /*<<< orphan*/  IPATH_SDMA_RUNNING ; 
 int /*<<< orphan*/  IPATH_SDMA_SHUTDOWN ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_ib_piobufavail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ipath_restart_sdma(struct ipath_devdata *dd)
{
	unsigned long flags;
	int needed = 1;

	if (!(dd->ipath_flags & IPATH_HAS_SEND_DMA))
		goto bail;

	/*
	 * First, make sure we should, which is to say,
	 * check that we are "RUNNING" (not in teardown)
	 * and not "SHUTDOWN"
	 */
	spin_lock_irqsave(&dd->ipath_sdma_lock, flags);
	if (!test_bit(IPATH_SDMA_RUNNING, &dd->ipath_sdma_status)
		|| test_bit(IPATH_SDMA_SHUTDOWN, &dd->ipath_sdma_status))
			needed = 0;
	else {
		__clear_bit(IPATH_SDMA_DISABLED, &dd->ipath_sdma_status);
		__clear_bit(IPATH_SDMA_DISARMED, &dd->ipath_sdma_status);
		__clear_bit(IPATH_SDMA_ABORTING, &dd->ipath_sdma_status);
	}
	spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);
	if (!needed) {
		ipath_dbg("invalid attempt to restart SDMA, status 0x%08lx\n",
			dd->ipath_sdma_status);
		goto bail;
	}
	spin_lock_irqsave(&dd->ipath_sendctrl_lock, flags);
	/*
	 * First clear, just to be safe. Enable is only done
	 * in chip on 0->1 transition
	 */
	dd->ipath_sendctrl &= ~INFINIPATH_S_SDMAENABLE;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_sendctrl, dd->ipath_sendctrl);
	ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
	dd->ipath_sendctrl |= INFINIPATH_S_SDMAENABLE;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_sendctrl, dd->ipath_sendctrl);
	ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
	spin_unlock_irqrestore(&dd->ipath_sendctrl_lock, flags);

	/* notify upper layers */
	ipath_ib_piobufavail(dd->verbs_dev);

bail:
	return;
}