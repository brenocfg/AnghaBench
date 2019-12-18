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
struct fhci_usb {struct fhci_usb* actual_frame; struct fhci_hcd* fhci; } ;
struct fhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FHCI_PORT_POWER_OFF ; 
 int /*<<< orphan*/  fhci_config_transceiver (struct fhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_ep0_free (struct fhci_usb*) ; 
 int /*<<< orphan*/  kfree (struct fhci_usb*) ; 

__attribute__((used)) static void fhci_usb_free(void *lld)
{
	struct fhci_usb *usb = lld;
	struct fhci_hcd *fhci = usb->fhci;

	if (usb) {
		fhci_config_transceiver(fhci, FHCI_PORT_POWER_OFF);
		fhci_ep0_free(usb);
		kfree(usb->actual_frame);
		kfree(usb);
	}
}