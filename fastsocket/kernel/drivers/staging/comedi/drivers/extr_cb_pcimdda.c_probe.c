#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct comedi_device {TYPE_4__* board_ptr; } ;
struct comedi_devconfig {scalar_t__* options; } ;
struct TYPE_9__ {scalar_t__ device_id; } ;
struct TYPE_8__ {unsigned long registers; scalar_t__ dio_registers; struct pci_dev* pci_dev; } ;
struct TYPE_7__ {scalar_t__ dio_offset; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ number; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_COMPUTERBOARDS ; 
 int /*<<< orphan*/  REGS_BADRINDEX ; 
 TYPE_4__* boards ; 
 scalar_t__ comedi_pci_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devpriv ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_2__* thisboard ; 

__attribute__((used)) static int probe(struct comedi_device *dev, const struct comedi_devconfig *it)
{
	struct pci_dev *pcidev;
	int index;
	unsigned long registers;

	for (pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
	     pcidev != NULL;
	     pcidev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pcidev)) {
		/*  is it not a computer boards card? */
		if (pcidev->vendor != PCI_VENDOR_ID_COMPUTERBOARDS)
			continue;
		/*  loop through cards supported by this driver */
		for (index = 0; index < ARRAY_SIZE(boards); index++) {
			if (boards[index].device_id != pcidev->device)
				continue;
			/*  was a particular bus/slot requested? */
			if (it->options[0] || it->options[1]) {
				/*  are we on the wrong bus/slot? */
				if (pcidev->bus->number != it->options[0] ||
				    PCI_SLOT(pcidev->devfn) != it->options[1]) {
					continue;
				}
			}
			/* found ! */

			devpriv->pci_dev = pcidev;
			dev->board_ptr = boards + index;
			if (comedi_pci_enable(pcidev, thisboard->name)) {
				printk
				    ("cb_pcimdda: Failed to enable PCI device and request regions\n");
				return -EIO;
			}
			registers =
			    pci_resource_start(devpriv->pci_dev,
					       REGS_BADRINDEX);
			devpriv->registers = registers;
			devpriv->dio_registers
			    = devpriv->registers + thisboard->dio_offset;
			return 0;
		}
	}

	printk("cb_pcimdda: No supported ComputerBoards/MeasurementComputing "
	       "card found at the requested position\n");
	return -ENODEV;
}