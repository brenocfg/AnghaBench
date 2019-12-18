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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCI_CLASS_STORAGE_SCSI ; 
 int /*<<< orphan*/  driver_name ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_pci_ports(void)
{
#if defined(CONFIG_PCI)
	struct pci_dev *dev = NULL;

	while ((dev = pci_get_class(PCI_CLASS_STORAGE_SCSI << 8, dev))) {
#if defined(DEBUG_PCI_DETECT)
		printk("%s: enable_pci_ports, bus %d, devfn 0x%x.\n",
		       driver_name, dev->bus->number, dev->devfn);
#endif

		if (pci_enable_device(dev))
			printk
			    ("%s: warning, pci_enable_device failed, bus %d devfn 0x%x.\n",
			     driver_name, dev->bus->number, dev->devfn);
	}

#endif				/* end CONFIG_PCI */
}