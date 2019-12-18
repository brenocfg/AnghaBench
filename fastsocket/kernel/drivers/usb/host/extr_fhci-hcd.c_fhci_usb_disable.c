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
typedef  int /*<<< orphan*/  u32 ;
struct fhci_usb {scalar_t__ port_status; TYPE_2__* fhci; } ;
struct fhci_hcd {struct fhci_usb* usb_lld; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_mod; } ;

/* Variables and functions */
 scalar_t__ FHCI_PORT_FULL ; 
 scalar_t__ FHCI_PORT_LOW ; 
 int /*<<< orphan*/  USB_MODE_EN ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_device_disconnected_interrupt (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_port_disable (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_usb_disable_interrupt (struct fhci_usb*) ; 

__attribute__((used)) static u32 fhci_usb_disable(struct fhci_hcd *fhci)
{
	struct fhci_usb *usb = fhci->usb_lld;

	fhci_usb_disable_interrupt(usb);
	fhci_port_disable(fhci);

	/* disable the usb controller */
	if (usb->port_status == FHCI_PORT_FULL ||
			usb->port_status == FHCI_PORT_LOW)
		fhci_device_disconnected_interrupt(fhci);

	clrbits8(&usb->fhci->regs->usb_mod, USB_MODE_EN);

	return 0;
}