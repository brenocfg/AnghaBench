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
struct vhci_hcd {int* port_status; int /*<<< orphan*/  lock; } ;
struct usb_hcd {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 scalar_t__ HC_STATE_SUSPENDED ; 
 int PORT_C_MASK ; 
 int VHCI_NPORTS ; 
 struct vhci_hcd* hcd_to_vhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rh (char*,...) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int) ; 

__attribute__((used)) static int vhci_hub_status(struct usb_hcd *hcd, char *buf)
{
	struct vhci_hcd	*vhci;
	unsigned long	flags;
	int		retval = 0;

	/* the enough buffer is allocated according to USB_MAXCHILDREN */
	unsigned long	*event_bits = (unsigned long *) buf;
	int		rhport;
	int		changed = 0;


	*event_bits = 0;

	vhci = hcd_to_vhci(hcd);

	spin_lock_irqsave(&vhci->lock, flags);
	if (!HCD_HW_ACCESSIBLE(hcd)) {
		usbip_dbg_vhci_rh("hw accessible flag in on?\n");
		goto done;
	}

	/* check pseudo status register for each port */
	for (rhport = 0; rhport < VHCI_NPORTS; rhport++) {
		if ((vhci->port_status[rhport] & PORT_C_MASK)) {
			/* The status of a port has been changed, */
			usbip_dbg_vhci_rh("port %d is changed\n", rhport);

			*event_bits |= 1 << (rhport + 1);
			changed = 1;
		}
	}

	usbip_uinfo("changed %d\n", changed);

	if (hcd->state == HC_STATE_SUSPENDED)
		usb_hcd_resume_root_hub(hcd);

	if (changed)
		retval = 1 + (VHCI_NPORTS / 8);
	else
		retval = 0;

done:
	spin_unlock_irqrestore(&vhci->lock, flags);
	return retval;
}