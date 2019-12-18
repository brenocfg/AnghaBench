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
struct fhci_usb {int /*<<< orphan*/  transfer_confirm; int /*<<< orphan*/  vroot_hub; int /*<<< orphan*/  hc_list; struct fhci_hcd* fhci; } ;
struct fhci_hcd {int /*<<< orphan*/  vroot_hub; int /*<<< orphan*/  hc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fhci_err (struct fhci_hcd*,char*) ; 
 int /*<<< orphan*/  fhci_transfer_confirm_callback ; 
 struct fhci_usb* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fhci_usb *fhci_create_lld(struct fhci_hcd *fhci)
{
	struct fhci_usb *usb;

	/* allocate memory for SCC data structure */
	usb = kzalloc(sizeof(*usb), GFP_KERNEL);
	if (!usb) {
		fhci_err(fhci, "no memory for SCC data struct\n");
		return NULL;
	}

	usb->fhci = fhci;
	usb->hc_list = fhci->hc_list;
	usb->vroot_hub = fhci->vroot_hub;

	usb->transfer_confirm = fhci_transfer_confirm_callback;

	return usb;
}