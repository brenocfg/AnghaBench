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
typedef  union xhci_trb {int dummy; } xhci_trb ;
struct xhci_hcd {int xhc_state; int /*<<< orphan*/  lock; } ;
struct xhci_command {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary_hcd; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int XHCI_STATE_DYING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hc_died (int /*<<< orphan*/ ) ; 
 int xhci_abort_cmd_ring (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 int xhci_queue_cd (struct xhci_hcd*,struct xhci_command*,union xhci_trb*) ; 
 TYPE_1__* xhci_to_hcd (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

int xhci_cancel_cmd(struct xhci_hcd *xhci, struct xhci_command *command,
		union xhci_trb *cmd_trb)
{
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&xhci->lock, flags);

	if (xhci->xhc_state & XHCI_STATE_DYING) {
		xhci_warn(xhci, "Abort the command ring,"
				" but the xHCI is dead.\n");
		retval = -ESHUTDOWN;
		goto fail;
	}

	/* queue the cmd desriptor to cancel_cmd_list */
	retval = xhci_queue_cd(xhci, command, cmd_trb);
	if (retval) {
		xhci_warn(xhci, "Queuing command descriptor failed.\n");
		goto fail;
	}

	/* abort command ring */
	retval = xhci_abort_cmd_ring(xhci);
	if (retval) {
		xhci_err(xhci, "Abort command ring failed\n");
		if (unlikely(retval == -ESHUTDOWN)) {
			spin_unlock_irqrestore(&xhci->lock, flags);
			usb_hc_died(xhci_to_hcd(xhci)->primary_hcd);
			xhci_dbg(xhci, "xHCI host controller is dead.\n");
			return retval;
		}
	}

fail:
	spin_unlock_irqrestore(&xhci->lock, flags);
	return retval;
}