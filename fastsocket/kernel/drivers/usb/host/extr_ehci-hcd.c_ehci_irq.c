#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_hcd {scalar_t__ state; int /*<<< orphan*/  rh_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  reclaim; int /*<<< orphan*/  error; int /*<<< orphan*/  normal; } ;
struct ehci_hcd {scalar_t__* reset_done; int /*<<< orphan*/  lock; TYPE_2__* regs; int /*<<< orphan*/  suspended_ports; scalar_t__ has_ppcd; int /*<<< orphan*/  hcs_params; TYPE_1__ stats; scalar_t__ reclaim; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  configured_flag; int /*<<< orphan*/ * port_status; int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int CMD_RUN ; 
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 unsigned int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 scalar_t__ HC_STATE_HALT ; 
 int INTR_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PORT_OWNER ; 
 int PORT_PE ; 
 int PORT_RESUME ; 
 int PORT_SUSPEND ; 
 int STS_ERR ; 
 int STS_FATAL ; 
 int STS_IAA ; 
 int STS_INT ; 
 int STS_PCD ; 
 int /*<<< orphan*/  dbg_cmd (struct ehci_hcd*,char*,int) ; 
 int /*<<< orphan*/  dbg_status (struct ehci_hcd*,char*,int) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,...) ; 
 int /*<<< orphan*/  ehci_err (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_halt (struct ehci_hcd*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_reset (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_work (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct ehci_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hc_died (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

__attribute__((used)) static irqreturn_t ehci_irq (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			status, masked_status, pcd_status = 0, cmd;
	int			bh;

	spin_lock (&ehci->lock);

	status = ehci_readl(ehci, &ehci->regs->status);

	/* e.g. cardbus physical eject */
	if (status == ~(u32) 0) {
		ehci_dbg (ehci, "device removed\n");
		goto dead;
	}

	/* Shared IRQ? */
	masked_status = status & INTR_MASK;
	if (!masked_status || unlikely(hcd->state == HC_STATE_HALT)) {
		spin_unlock(&ehci->lock);
		return IRQ_NONE;
	}

	/* clear (just) interrupts */
	ehci_writel(ehci, masked_status, &ehci->regs->status);
	cmd = ehci_readl(ehci, &ehci->regs->command);
	bh = 0;

#ifdef	VERBOSE_DEBUG
	/* unrequested/ignored: Frame List Rollover */
	dbg_status (ehci, "irq", status);
#endif

	/* INT, ERR, and IAA interrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	if (likely ((status & (STS_INT|STS_ERR)) != 0)) {
		if (likely ((status & STS_ERR) == 0))
			COUNT (ehci->stats.normal);
		else
			COUNT (ehci->stats.error);
		bh = 1;
	}

	/* complete the unlinking of some qh [4.15.2.3] */
	if (status & STS_IAA) {
		/* guard against (alleged) silicon errata */
		if (cmd & CMD_IAAD) {
			ehci_writel(ehci, cmd & ~CMD_IAAD,
					&ehci->regs->command);
			ehci_dbg(ehci, "IAA with IAAD still set?\n");
		}
		if (ehci->reclaim) {
			COUNT(ehci->stats.reclaim);
			end_unlink_async(ehci);
		} else
			ehci_dbg(ehci, "IAA with nothing to reclaim?\n");
	}

	/* remote wakeup [4.3.1] */
	if (status & STS_PCD) {
		unsigned	i = HCS_N_PORTS (ehci->hcs_params);
		u32		ppcd = 0;

		/* kick root hub later */
		pcd_status = status;

		/* resume root hub? */
		if (!(cmd & CMD_RUN))
			usb_hcd_resume_root_hub(hcd);

		/* get per-port change detect bits */
		if (ehci->has_ppcd)
			ppcd = status >> 16;

		while (i--) {
			int pstatus;

			/* leverage per-port change bits feature */
			if (ehci->has_ppcd && !(ppcd & (1 << i)))
				continue;
			pstatus = ehci_readl(ehci,
					 &ehci->regs->port_status[i]);

			if (pstatus & PORT_OWNER)
				continue;
			if (!(test_bit(i, &ehci->suspended_ports) &&
					((pstatus & PORT_RESUME) ||
						!(pstatus & PORT_SUSPEND)) &&
					(pstatus & PORT_PE) &&
					ehci->reset_done[i] == 0))
				continue;

			/* start 20 msec resume signaling from this port,
			 * and make khubd collect PORT_STAT_C_SUSPEND to
			 * stop that signaling.  Use 5 ms extra for safety,
			 * like usb_port_resume() does.
			 */
			ehci->reset_done[i] = jiffies + msecs_to_jiffies(25);
			ehci_dbg (ehci, "port %d remote wakeup\n", i + 1);
			mod_timer(&hcd->rh_timer, ehci->reset_done[i]);
		}
	}

	/* PCI errors [4.15.2.4] */
	if (unlikely ((status & STS_FATAL) != 0)) {
		ehci_err(ehci, "fatal error\n");
		dbg_cmd(ehci, "fatal", cmd);
		dbg_status(ehci, "fatal", status);
		ehci_halt(ehci);
dead:
		ehci_reset(ehci);
		ehci_writel(ehci, 0, &ehci->regs->configured_flag);
		usb_hc_died(hcd);
		/* generic layer kills/unlinks all urbs, then
		 * uses ehci_stop to clean up the rest
		 */
		bh = 1;
	}

	if (bh)
		ehci_work (ehci);
	spin_unlock (&ehci->lock);
	if (pcd_status)
		usb_hcd_poll_rh_status(hcd);
	return IRQ_HANDLED;
}