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
typedef  int u32 ;
struct xhci_hcd {int num_usb3_ports; int port_status_u0; int /*<<< orphan*/  comp_mode_recovery_timer; struct usb_hcd* shared_hcd; int /*<<< orphan*/ * usb3_ports; } ;
struct usb_hcd {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MODE_RCVRY_MSECS ; 
 scalar_t__ HC_STATE_SUSPENDED ; 
 int PORT_PLS_MASK ; 
 int USB_SS_PORT_LS_COMP_MOD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 int xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compliance_mode_recovery(unsigned long arg)
{
	struct xhci_hcd *xhci;
	struct usb_hcd *hcd;
	u32 temp;
	int i;

	xhci = (struct xhci_hcd *)arg;

	for (i = 0; i < xhci->num_usb3_ports; i++) {
		temp = xhci_readl(xhci, xhci->usb3_ports[i]);
		if ((temp & PORT_PLS_MASK) == USB_SS_PORT_LS_COMP_MOD) {
			/*
			 * Compliance Mode Detected. Letting USB Core
			 * handle the Warm Reset
			 */
			xhci_dbg(xhci, "Compliance mode detected->port %d\n",
					i + 1);
			xhci_dbg(xhci, "Attempting compliance mode recovery\n");
			hcd = xhci->shared_hcd;

			if (hcd->state == HC_STATE_SUSPENDED)
				usb_hcd_resume_root_hub(hcd);

			usb_hcd_poll_rh_status(hcd);
		}
	}

	if (xhci->port_status_u0 != ((1 << xhci->num_usb3_ports)-1))
		mod_timer(&xhci->comp_mode_recovery_timer,
			jiffies + msecs_to_jiffies(COMP_MODE_RCVRY_MSECS));
}