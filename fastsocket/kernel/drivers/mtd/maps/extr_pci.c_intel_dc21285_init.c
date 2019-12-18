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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int bankwidth; unsigned long size; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct map_pci_info {int /*<<< orphan*/  base; TYPE_1__ map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  ioremap_nocache (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mtd_pci_read32 ; 
 int /*<<< orphan*/  mtd_pci_write32 ; 
 int /*<<< orphan*/  pci_enable_rom (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_dc21285_init(struct pci_dev *dev, struct map_pci_info *map)
{
	unsigned long base, len;

	base = pci_resource_start(dev, PCI_ROM_RESOURCE);
	len  = pci_resource_len(dev, PCI_ROM_RESOURCE);

	if (!len || !base) {
		/*
		 * No ROM resource
		 */
		base = pci_resource_start(dev, 2);
		len  = pci_resource_len(dev, 2);

		/*
		 * We need to re-allocate PCI BAR2 address range to the
		 * PCI ROM BAR, and disable PCI BAR2.
		 */
	} else {
		/*
		 * Hmm, if an address was allocated to the ROM resource, but
		 * not enabled, should we be allocating a new resource for it
		 * or simply enabling it?
		 */
		pci_enable_rom(dev);
		printk("%s: enabling expansion ROM\n", pci_name(dev));
	}

	if (!len || !base)
		return -ENXIO;

	map->map.bankwidth = 4;
	map->map.read = mtd_pci_read32,
	map->map.write = mtd_pci_write32,
	map->map.size     = len;
	map->base         = ioremap_nocache(base, len);

	if (!map->base)
		return -ENOMEM;

	return 0;
}