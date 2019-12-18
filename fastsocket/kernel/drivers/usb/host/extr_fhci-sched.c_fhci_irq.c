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
typedef  int u16 ;
struct usb_hcd {int dummy; } ;
struct fhci_usb {scalar_t__ port_status; int saved_msk; TYPE_2__* fhci; } ;
struct fhci_hcd {int /*<<< orphan*/  lock; struct fhci_usb* usb_lld; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_mask; int /*<<< orphan*/  usb_event; } ;

/* Variables and functions */
 scalar_t__ FHCI_PORT_DISABLED ; 
 scalar_t__ FHCI_PORT_DISCONNECTING ; 
 scalar_t__ FHCI_PORT_FULL ; 
 scalar_t__ FHCI_PORT_LOW ; 
 scalar_t__ FHCI_PORT_WAITING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int USB_E_IDLE_MASK ; 
 int USB_E_MSF_MASK ; 
 int USB_E_RESET_MASK ; 
 int USB_E_SFT_MASK ; 
 int USB_E_SOF_MASK ; 
 int USB_E_TXB_MASK ; 
 int USB_E_TXE1_MASK ; 
 int /*<<< orphan*/  abort_transmission (struct fhci_usb*) ; 
 int /*<<< orphan*/  fhci_dbg_isr (struct fhci_hcd*,int) ; 
 int /*<<< orphan*/  fhci_device_connected_interrupt (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_device_disconnected_interrupt (struct fhci_hcd*) ; 
 int fhci_ioports_check_bus_state (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_tx_conf_interrupt (struct fhci_usb*) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sof_interrupt (struct fhci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

irqreturn_t fhci_irq(struct usb_hcd *hcd)
{
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);
	struct fhci_usb *usb;
	u16 usb_er = 0;
	unsigned long flags;

	spin_lock_irqsave(&fhci->lock, flags);

	usb = fhci->usb_lld;

	usb_er |= in_be16(&usb->fhci->regs->usb_event) &
		  in_be16(&usb->fhci->regs->usb_mask);

	/* clear event bits for next time */
	out_be16(&usb->fhci->regs->usb_event, usb_er);

	fhci_dbg_isr(fhci, usb_er);

	if (usb_er & USB_E_RESET_MASK) {
		if ((usb->port_status == FHCI_PORT_FULL) ||
				(usb->port_status == FHCI_PORT_LOW)) {
			fhci_device_disconnected_interrupt(fhci);
			usb_er &= ~USB_E_IDLE_MASK;
		} else if (usb->port_status == FHCI_PORT_WAITING) {
			usb->port_status = FHCI_PORT_DISCONNECTING;

			/* Turn on IDLE since we want to disconnect */
			usb->saved_msk |= USB_E_IDLE_MASK;
			out_be16(&usb->fhci->regs->usb_event,
				 usb->saved_msk);
		} else if (usb->port_status == FHCI_PORT_DISABLED) {
			if (fhci_ioports_check_bus_state(fhci) == 1)
				fhci_device_connected_interrupt(fhci);
		}
		usb_er &= ~USB_E_RESET_MASK;
	}

	if (usb_er & USB_E_MSF_MASK) {
		abort_transmission(fhci->usb_lld);
		usb_er &= ~USB_E_MSF_MASK;
	}

	if (usb_er & (USB_E_SOF_MASK | USB_E_SFT_MASK)) {
		sof_interrupt(fhci);
		usb_er &= ~(USB_E_SOF_MASK | USB_E_SFT_MASK);
	}

	if (usb_er & USB_E_TXB_MASK) {
		fhci_tx_conf_interrupt(fhci->usb_lld);
		usb_er &= ~USB_E_TXB_MASK;
	}

	if (usb_er & USB_E_TXE1_MASK) {
		fhci_tx_conf_interrupt(fhci->usb_lld);
		usb_er &= ~USB_E_TXE1_MASK;
	}

	if (usb_er & USB_E_IDLE_MASK) {
		if (usb->port_status == FHCI_PORT_DISABLED) {
			usb_er &= ~USB_E_RESET_MASK;
			fhci_device_connected_interrupt(fhci);
		} else if (usb->port_status ==
				FHCI_PORT_DISCONNECTING) {
			/* XXX usb->port_status = FHCI_PORT_WAITING; */
			/* Disable IDLE */
			usb->saved_msk &= ~USB_E_IDLE_MASK;
			out_be16(&usb->fhci->regs->usb_mask,
				 usb->saved_msk);
		} else {
			fhci_dbg_isr(fhci, -1);
		}

		usb_er &= ~USB_E_IDLE_MASK;
	}

	spin_unlock_irqrestore(&fhci->lock, flags);

	return IRQ_HANDLED;
}