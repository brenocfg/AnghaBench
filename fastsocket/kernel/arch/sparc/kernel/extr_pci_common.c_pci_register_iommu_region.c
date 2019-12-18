#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {char* name; int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct pci_pbm_info {TYPE_2__ mem_space; TYPE_1__* op; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_BUSY ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_printf (char*) ; 
 int /*<<< orphan*/  request_resource (TYPE_2__*,struct resource*) ; 

__attribute__((used)) static void pci_register_iommu_region(struct pci_pbm_info *pbm)
{
	const u32 *vdma = of_get_property(pbm->op->node, "virtual-dma", NULL);

	if (vdma) {
		struct resource *rp = kzalloc(sizeof(*rp), GFP_KERNEL);

		if (!rp) {
			prom_printf("Cannot allocate IOMMU resource.\n");
			prom_halt();
		}
		rp->name = "IOMMU";
		rp->start = pbm->mem_space.start + (unsigned long) vdma[0];
		rp->end = rp->start + (unsigned long) vdma[1] - 1UL;
		rp->flags = IORESOURCE_BUSY;
		request_resource(&pbm->mem_space, rp);
	}
}