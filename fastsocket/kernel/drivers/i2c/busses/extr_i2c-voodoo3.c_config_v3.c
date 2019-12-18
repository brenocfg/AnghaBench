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
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* resource; } ;
struct TYPE_2__ {unsigned long start; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned long PCI_BASE_ADDRESS_MEM_MASK ; 
 scalar_t__ REG ; 
 scalar_t__ REG2 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ ioaddr ; 
 scalar_t__ ioremap_nocache (unsigned long,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int config_v3(struct pci_dev *dev)
{
	unsigned long cadr;

	/* map Voodoo3 memory */
	cadr = dev->resource[0].start;
	cadr &= PCI_BASE_ADDRESS_MEM_MASK;
	ioaddr = ioremap_nocache(cadr, 0x1000);
	if (ioaddr) {
		writel(0x8160, ioaddr + REG2);
		writel(0xcffc0020, ioaddr + REG);
		dev_info(&dev->dev, "Using Banshee/Voodoo3 I2C device at %p\n", ioaddr);
		return 0;
	}
	return -ENODEV;
}