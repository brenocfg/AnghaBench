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
typedef  int /*<<< orphan*/  u32 ;
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct iommu {unsigned long page_table_map_base; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct pci_pbm_info* host_controller; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HV_PCI_TSBID (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long IO_PAGE_ALIGN (size_t) ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,unsigned long,unsigned long) ; 
 unsigned long pci_sun4v_iommu_demap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dma_4v_free_coherent(struct device *dev, size_t size, void *cpu,
				 dma_addr_t dvma)
{
	struct pci_pbm_info *pbm;
	struct iommu *iommu;
	unsigned long flags, order, npages, entry;
	u32 devhandle;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	devhandle = pbm->devhandle;
	entry = ((dvma - iommu->page_table_map_base) >> IO_PAGE_SHIFT);

	spin_lock_irqsave(&iommu->lock, flags);

	iommu_range_free(iommu, dvma, npages);

	do {
		unsigned long num;

		num = pci_sun4v_iommu_demap(devhandle, HV_PCI_TSBID(0, entry),
					    npages);
		entry += num;
		npages -= num;
	} while (npages != 0);

	spin_unlock_irqrestore(&iommu->lock, flags);

	order = get_order(size);
	if (order < 10)
		free_pages((unsigned long)cpu, order);
}