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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI6208_DRIVER_NAME ; 
 scalar_t__ comedi_pci_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_end (struct pci_dev*,int) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

__attribute__((used)) static int
pci6208_pci_setup(struct pci_dev *pci_dev, unsigned long *io_base_ptr,
		  int dev_minor)
{
	unsigned long io_base, io_range, lcr_io_base, lcr_io_range;

	/*  Enable PCI device and request regions */
	if (comedi_pci_enable(pci_dev, PCI6208_DRIVER_NAME) < 0) {
		printk
		    ("comedi%d: Failed to enable PCI device and request regions\n",
		     dev_minor);
		return -EIO;
	}
	/*  Read local configuration register base address [PCI_BASE_ADDRESS #1]. */
	lcr_io_base = pci_resource_start(pci_dev, 1);
	lcr_io_range = pci_resource_len(pci_dev, 1);

	printk("comedi%d: local config registers at address 0x%4lx [0x%4lx]\n",
	       dev_minor, lcr_io_base, lcr_io_range);

	/*  Read PCI6208 register base address [PCI_BASE_ADDRESS #2]. */
	io_base = pci_resource_start(pci_dev, 2);
	io_range = pci_resource_end(pci_dev, 2) - io_base + 1;

	printk("comedi%d: 6208 registers at address 0x%4lx [0x%4lx]\n",
	       dev_minor, io_base, io_range);

	*io_base_ptr = io_base;
	/* devpriv->io_range = io_range; */
	/* devpriv->is_valid=0; */
	/* devpriv->lcr_io_base=lcr_io_base; */
	/* devpriv->lcr_io_range=lcr_io_range; */

	return 0;
}