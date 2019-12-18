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
struct iommu {int page_table_map_base; int /*<<< orphan*/  lock; int /*<<< orphan*/ * page_table; } ;
struct TYPE_2__ {struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  iopte_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int IO_PAGE_ALIGN (size_t) ; 
 int IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dma_4u_free_coherent(struct device *dev, size_t size,
				 void *cpu, dma_addr_t dvma)
{
	struct iommu *iommu;
	iopte_t *iopte;
	unsigned long flags, order, npages;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;
	iopte = iommu->page_table +
		((dvma - iommu->page_table_map_base) >> IO_PAGE_SHIFT);

	spin_lock_irqsave(&iommu->lock, flags);

	iommu_range_free(iommu, dvma, npages);

	spin_unlock_irqrestore(&iommu->lock, flags);

	order = get_order(size);
	if (order < 10)
		free_pages((unsigned long)cpu, order);
}