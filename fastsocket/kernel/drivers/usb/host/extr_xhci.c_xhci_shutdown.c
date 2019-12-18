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
struct xhci_hcd {int quirks; TYPE_2__* op_regs; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int XHCI_SPURIOUS_REBOOT ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_disable_xhci_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_msix (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_halt (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 

void xhci_shutdown(struct usb_hcd *hcd)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);

	if (xhci->quirks & XHCI_SPURIOUS_REBOOT)
		usb_disable_xhci_ports(to_pci_dev(hcd->self.controller));

	spin_lock_irq(&xhci->lock);
	xhci_halt(xhci);
	spin_unlock_irq(&xhci->lock);

	xhci_cleanup_msix(xhci);

	xhci_dbg(xhci, "xhci_shutdown completed - status = %x\n",
		    xhci_readl(xhci, &xhci->op_regs->status));
}