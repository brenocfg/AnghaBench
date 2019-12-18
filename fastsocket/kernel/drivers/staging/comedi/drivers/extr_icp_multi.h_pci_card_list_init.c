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
struct pcilst_struct {unsigned short vendor; int /*<<< orphan*/  irq; int /*<<< orphan*/ * io_addr; int /*<<< orphan*/  pci_func; int /*<<< orphan*/  pci_slot; int /*<<< orphan*/  pci_bus; int /*<<< orphan*/  device; struct pcilst_struct* next; int /*<<< orphan*/  pcidev; } ;
struct pci_dev {unsigned short vendor; int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_1__* bus; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct pcilst_struct* inova_devices ; 
 struct pcilst_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pcilst_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_card_list_display () ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void pci_card_list_init(unsigned short pci_vendor, char display)
{
	struct pci_dev *pcidev;
	struct pcilst_struct *inova, *last;
	int i;

	inova_devices = NULL;
	last = NULL;

	for (pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
	     pcidev != NULL;
	     pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pcidev)) {
		if (pcidev->vendor == pci_vendor) {
			inova = kmalloc(sizeof(*inova), GFP_KERNEL);
			if (!inova) {
				printk
				    ("icp_multi: pci_card_list_init: allocation failed\n");
				pci_dev_put(pcidev);
				break;
			}
			memset(inova, 0, sizeof(*inova));

			inova->pcidev = pci_dev_get(pcidev);
			if (last) {
				last->next = inova;
			} else {
				inova_devices = inova;
			}
			last = inova;

			inova->vendor = pcidev->vendor;
			inova->device = pcidev->device;
			inova->pci_bus = pcidev->bus->number;
			inova->pci_slot = PCI_SLOT(pcidev->devfn);
			inova->pci_func = PCI_FUNC(pcidev->devfn);
			/* Note: resources may be invalid if PCI device
			 * not enabled, but they are corrected in
			 * pci_card_alloc. */
			for (i = 0; i < 5; i++)
				inova->io_addr[i] =
				    pci_resource_start(pcidev, i);
			inova->irq = pcidev->irq;
		}
	}

	if (display)
		pci_card_list_display();
}