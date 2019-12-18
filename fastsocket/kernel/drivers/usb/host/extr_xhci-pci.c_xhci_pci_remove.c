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
struct xhci_hcd {scalar_t__ shared_hcd; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_hcd*) ; 
 int /*<<< orphan*/  pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_hcd_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_put_hcd (scalar_t__) ; 
 int /*<<< orphan*/  usb_remove_hcd (scalar_t__) ; 

__attribute__((used)) static void xhci_pci_remove(struct pci_dev *dev)
{
	struct xhci_hcd *xhci;

	xhci = hcd_to_xhci(pci_get_drvdata(dev));
	if (xhci->shared_hcd) {
		usb_remove_hcd(xhci->shared_hcd);
		usb_put_hcd(xhci->shared_hcd);
	}
	usb_hcd_pci_remove(dev);
	kfree(xhci);
}