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
struct pci_dev {int /*<<< orphan*/ * resource; struct pci_controller* sysdata; } ;
struct pci_controller {scalar_t__ sparse_mem_base; scalar_t__ dense_mem_base; } ;
struct pci_bus_region {unsigned long end; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_resource_to_bus (struct pci_dev*,struct pci_bus_region*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sparse_mem_mmap_fits(struct pci_dev *pdev, int num)
{
	struct pci_bus_region bar;
	struct pci_controller *hose = pdev->sysdata;
	long dense_offset;
	unsigned long sparse_size;

	pcibios_resource_to_bus(pdev, &bar, &pdev->resource[num]);

	/* All core logic chips have 4G sparse address space, except
	   CIA which has 16G (see xxx_SPARSE_MEM and xxx_DENSE_MEM
	   definitions in asm/core_xxx.h files). This corresponds
	   to 128M or 512M of the bus space. */
	dense_offset = (long)(hose->dense_mem_base - hose->sparse_mem_base);
	sparse_size = dense_offset >= 0x400000000UL ? 0x20000000 : 0x8000000;

	return bar.end < sparse_size;
}