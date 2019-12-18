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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  cell_dma_dev_setup_fixed (struct device*) ; 
 int /*<<< orphan*/  cell_dma_direct_offset ; 
 int /*<<< orphan*/  cell_get_iommu_table (struct device*) ; 
 int /*<<< orphan*/  dma_direct_ops ; 
 int /*<<< orphan*/  dma_iommu_fixed_ops ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 int /*<<< orphan*/ * get_dma_ops (struct device*) ; 
 int /*<<< orphan*/ * get_pci_dma_ops () ; 
 int /*<<< orphan*/  set_dma_offset (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iommu_table_base (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cell_dma_dev_setup(struct device *dev)
{
	/* Order is important here, these are not mutually exclusive */
	if (get_dma_ops(dev) == &dma_iommu_fixed_ops)
		cell_dma_dev_setup_fixed(dev);
	else if (get_pci_dma_ops() == &dma_iommu_ops)
		set_iommu_table_base(dev, cell_get_iommu_table(dev));
	else if (get_pci_dma_ops() == &dma_direct_ops)
		set_dma_offset(dev, cell_dma_direct_offset);
	else
		BUG();
}