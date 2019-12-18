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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct pci_dev {scalar_t__ device; scalar_t__ vendor; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct ohci_hcd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_QUIRK_SUPERIO ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI_DEVICE_ID_NS_87560_LIO ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_NS ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd*,char*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ohci_quirk_ns(struct usb_hcd *hcd)
{
	struct pci_dev *pdev = to_pci_dev(hcd->self.controller);
	struct pci_dev	*b;

	b  = pci_get_slot (pdev->bus, PCI_DEVFN (PCI_SLOT (pdev->devfn), 1));
	if (b && b->device == PCI_DEVICE_ID_NS_87560_LIO
	    && b->vendor == PCI_VENDOR_ID_NS) {
		struct ohci_hcd	*ohci = hcd_to_ohci (hcd);

		ohci->flags |= OHCI_QUIRK_SUPERIO;
		ohci_dbg (ohci, "Using NSC SuperIO setup\n");
	}
	pci_dev_put(b);

	return 0;
}