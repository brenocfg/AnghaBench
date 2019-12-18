#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {unsigned long start; unsigned long end; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct pci_pbm_info {unsigned long config_space; TYPE_2__ mem_space; TYPE_2__ io_space; int /*<<< orphan*/  name; TYPE_1__* op; } ;
struct linux_prom_pci_ranges {int parent_phys_hi; int parent_phys_lo; int size_hi; int size_lo; int child_phys_hi; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  ioport_resource ; 
 struct linux_prom_pci_ranges* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  pci_register_iommu_region (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_register_legacy_regions (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  request_resource (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ tlb_type ; 

void pci_determine_mem_io_space(struct pci_pbm_info *pbm)
{
	const struct linux_prom_pci_ranges *pbm_ranges;
	int i, saw_mem, saw_io;
	int num_pbm_ranges;

	saw_mem = saw_io = 0;
	pbm_ranges = of_get_property(pbm->op->node, "ranges", &i);
	if (!pbm_ranges) {
		prom_printf("PCI: Fatal error, missing PBM ranges property "
			    " for %s\n",
			    pbm->name);
		prom_halt();
	}

	num_pbm_ranges = i / sizeof(*pbm_ranges);

	for (i = 0; i < num_pbm_ranges; i++) {
		const struct linux_prom_pci_ranges *pr = &pbm_ranges[i];
		unsigned long a, size;
		u32 parent_phys_hi, parent_phys_lo;
		u32 size_hi, size_lo;
		int type;

		parent_phys_hi = pr->parent_phys_hi;
		parent_phys_lo = pr->parent_phys_lo;
		if (tlb_type == hypervisor)
			parent_phys_hi &= 0x0fffffff;

		size_hi = pr->size_hi;
		size_lo = pr->size_lo;

		type = (pr->child_phys_hi >> 24) & 0x3;
		a = (((unsigned long)parent_phys_hi << 32UL) |
		     ((unsigned long)parent_phys_lo  <<  0UL));
		size = (((unsigned long)size_hi << 32UL) |
			((unsigned long)size_lo  <<  0UL));

		switch (type) {
		case 0:
			/* PCI config space, 16MB */
			pbm->config_space = a;
			break;

		case 1:
			/* 16-bit IO space, 16MB */
			pbm->io_space.start = a;
			pbm->io_space.end = a + size - 1UL;
			pbm->io_space.flags = IORESOURCE_IO;
			saw_io = 1;
			break;

		case 2:
			/* 32-bit MEM space, 2GB */
			pbm->mem_space.start = a;
			pbm->mem_space.end = a + size - 1UL;
			pbm->mem_space.flags = IORESOURCE_MEM;
			saw_mem = 1;
			break;

		case 3:
			/* XXX 64-bit MEM handling XXX */

		default:
			break;
		};
	}

	if (!saw_io || !saw_mem) {
		prom_printf("%s: Fatal error, missing %s PBM range.\n",
			    pbm->name,
			    (!saw_io ? "IO" : "MEM"));
		prom_halt();
	}

	printk("%s: PCI IO[%llx] MEM[%llx]\n",
	       pbm->name,
	       pbm->io_space.start,
	       pbm->mem_space.start);

	pbm->io_space.name = pbm->mem_space.name = pbm->name;

	request_resource(&ioport_resource, &pbm->io_space);
	request_resource(&iomem_resource, &pbm->mem_space);

	pci_register_legacy_regions(&pbm->io_space,
				    &pbm->mem_space);
	pci_register_iommu_region(pbm);
}