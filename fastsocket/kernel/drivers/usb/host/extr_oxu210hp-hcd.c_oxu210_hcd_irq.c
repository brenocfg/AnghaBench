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
typedef  int u32 ;
struct usb_hcd {scalar_t__ state; int /*<<< orphan*/  rh_timer; } ;
struct oxu_hcd {int reclaim_ready; scalar_t__* reset_done; int /*<<< orphan*/  lock; TYPE_1__* regs; int /*<<< orphan*/  hcs_params; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  configured_flag; int /*<<< orphan*/  command; int /*<<< orphan*/  status; int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */
 int CMD_RUN ; 
 unsigned int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 scalar_t__ HC_STATE_HALT ; 
 int INTR_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PORT_OWNER ; 
 int PORT_RESUME ; 
 int STS_ERR ; 
 int STS_FATAL ; 
 int STS_HALT ; 
 int STS_IAA ; 
 int STS_INT ; 
 int STS_PCD ; 
 int /*<<< orphan*/  dbg_cmd (struct oxu_hcd*,char*,int) ; 
 int /*<<< orphan*/  dbg_status (struct oxu_hcd*,char*,int) ; 
 int /*<<< orphan*/  ehci_reset (struct oxu_hcd*) ; 
 int /*<<< orphan*/  ehci_work (struct oxu_hcd*) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*,...) ; 
 int /*<<< orphan*/  oxu_err (struct oxu_hcd*,char*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hc_died (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t oxu210_hcd_irq(struct usb_hcd *hcd)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 status, pcd_status = 0;
	int bh;

	spin_lock(&oxu->lock);

	status = readl(&oxu->regs->status);

	/* e.g. cardbus physical eject */
	if (status == ~(u32) 0) {
		oxu_dbg(oxu, "device removed\n");
		goto dead;
	}

	/* Shared IRQ? */
	status &= INTR_MASK;
	if (!status || unlikely(hcd->state == HC_STATE_HALT)) {
		spin_unlock(&oxu->lock);
		return IRQ_NONE;
	}

	/* clear (just) interrupts */
	writel(status, &oxu->regs->status);
	readl(&oxu->regs->command);	/* unblock posted write */
	bh = 0;

#ifdef OXU_VERBOSE_DEBUG
	/* unrequested/ignored: Frame List Rollover */
	dbg_status(oxu, "irq", status);
#endif

	/* INT, ERR, and IAA interrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	if (likely((status & (STS_INT|STS_ERR)) != 0))
		bh = 1;

	/* complete the unlinking of some qh [4.15.2.3] */
	if (status & STS_IAA) {
		oxu->reclaim_ready = 1;
		bh = 1;
	}

	/* remote wakeup [4.3.1] */
	if (status & STS_PCD) {
		unsigned i = HCS_N_PORTS(oxu->hcs_params);
		pcd_status = status;

		/* resume root hub? */
		if (!(readl(&oxu->regs->command) & CMD_RUN))
			usb_hcd_resume_root_hub(hcd);

		while (i--) {
			int pstatus = readl(&oxu->regs->port_status[i]);

			if (pstatus & PORT_OWNER)
				continue;
			if (!(pstatus & PORT_RESUME)
					|| oxu->reset_done[i] != 0)
				continue;

			/* start 20 msec resume signaling from this port,
			 * and make khubd collect PORT_STAT_C_SUSPEND to
			 * stop that signaling.
			 */
			oxu->reset_done[i] = jiffies + msecs_to_jiffies(20);
			oxu_dbg(oxu, "port %d remote wakeup\n", i + 1);
			mod_timer(&hcd->rh_timer, oxu->reset_done[i]);
		}
	}

	/* PCI errors [4.15.2.4] */
	if (unlikely((status & STS_FATAL) != 0)) {
		/* bogus "fatal" IRQs appear on some chips... why?  */
		status = readl(&oxu->regs->status);
		dbg_cmd(oxu, "fatal", readl(&oxu->regs->command));
		dbg_status(oxu, "fatal", status);
		if (status & STS_HALT) {
			oxu_err(oxu, "fatal error\n");
dead:
			ehci_reset(oxu);
			writel(0, &oxu->regs->configured_flag);
			usb_hc_died(hcd);
			/* generic layer kills/unlinks all urbs, then
			 * uses oxu_stop to clean up the rest
			 */
			bh = 1;
		}
	}

	if (bh)
		ehci_work(oxu);
	spin_unlock(&oxu->lock);
	if (pcd_status & STS_PCD)
		usb_hcd_poll_rh_status(hcd);
	return IRQ_HANDLED;
}