#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct comedi_device {int /*<<< orphan*/  minor; TYPE_2__* board_ptr; } ;
struct TYPE_7__ {struct pci_dev* pci_dev; } ;
struct TYPE_6__ {scalar_t__ dev_id; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EIO ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_ADLINK ; 
 TYPE_3__* devpriv ; 
 TYPE_2__* pci6208_boards ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static int pci6208_find_device(struct comedi_device *dev, int bus, int slot)
{
	struct pci_dev *pci_dev;
	int i;

	for (pci_dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
	     pci_dev != NULL;
	     pci_dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pci_dev)) {
		if (pci_dev->vendor == PCI_VENDOR_ID_ADLINK) {
			for (i = 0; i < ARRAY_SIZE(pci6208_boards); i++) {
				if (pci6208_boards[i].dev_id == pci_dev->device) {
					/*  was a particular bus/slot requested? */
					if ((bus != 0) || (slot != 0)) {
						/*  are we on the wrong bus/slot? */
						if (pci_dev->bus->number
						    != bus ||
						    PCI_SLOT(pci_dev->devfn)
						    != slot) {
							continue;
						}
					}
					dev->board_ptr = pci6208_boards + i;
					goto found;
				}
			}
		}
	}

	printk("comedi%d: no supported board found! (req. bus/slot : %d/%d)\n",
	       dev->minor, bus, slot);
	return -EIO;

found:
	printk("comedi%d: found %s (b:s:f=%d:%d:%d) , irq=%d\n",
	       dev->minor,
	       pci6208_boards[i].name,
	       pci_dev->bus->number,
	       PCI_SLOT(pci_dev->devfn),
	       PCI_FUNC(pci_dev->devfn), pci_dev->irq);

	/*  TODO: Warn about non-tested boards. */
	/* switch(board->device_id) */
	/* { */
	/* }; */

	devpriv->pci_dev = pci_dev;

	return 0;
}