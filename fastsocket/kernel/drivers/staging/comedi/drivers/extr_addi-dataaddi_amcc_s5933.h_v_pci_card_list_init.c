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
struct pcilst_struct {unsigned short vendor; int /*<<< orphan*/  irq; int /*<<< orphan*/ * io_addr; int /*<<< orphan*/  pci_func; int /*<<< orphan*/  pci_slot; int /*<<< orphan*/  pci_bus; int /*<<< orphan*/  device; struct pcilst_struct* next; struct pci_dev* pcidev; } ;
struct pci_dev {unsigned short vendor; int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_1__* bus; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct pcilst_struct* amcc_devices ; 
 unsigned short* i_ADDIDATADeviceID ; 
 struct pcilst_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pcilst_struct*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  v_pci_card_list_display () ; 

void v_pci_card_list_init(unsigned short pci_vendor, char display)
{
	struct pci_dev *pcidev;
	struct pcilst_struct *amcc, *last;
	int i;
	int i_Count = 0;
	amcc_devices = NULL;
	last = NULL;

	for (pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
	     pcidev != NULL;
	     pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pcidev)) {
		for (i_Count = 0; i_Count < 2; i_Count++) {
			pci_vendor = i_ADDIDATADeviceID[i_Count];
			if (pcidev->vendor == pci_vendor) {
				amcc = kmalloc(sizeof(*amcc), GFP_KERNEL);
				if (amcc == NULL)
					continue;

				memset(amcc, 0, sizeof(*amcc));

				amcc->pcidev = pcidev;
				if (last)
					last->next = amcc;
				else
					amcc_devices = amcc;
				last = amcc;

				amcc->vendor = pcidev->vendor;
				amcc->device = pcidev->device;
				amcc->pci_bus = pcidev->bus->number;
				amcc->pci_slot = PCI_SLOT(pcidev->devfn);
				amcc->pci_func = PCI_FUNC(pcidev->devfn);
				/* Note: resources may be invalid if PCI device
				 * not enabled, but they are corrected in
				 * pci_card_alloc. */
				for (i = 0; i < 5; i++)
					amcc->io_addr[i] =
					    pci_resource_start(pcidev, i);
				amcc->irq = pcidev->irq;

			}
		}
	}

	if (display)
		v_pci_card_list_display();
}