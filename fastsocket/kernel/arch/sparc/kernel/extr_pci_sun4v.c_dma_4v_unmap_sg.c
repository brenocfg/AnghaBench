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
struct scatterlist {unsigned long dma_address; unsigned int dma_length; } ;
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct iommu {unsigned long page_table_map_base; int /*<<< orphan*/  lock; } ;
struct dma_attrs {int dummy; } ;
struct TYPE_2__ {struct pci_pbm_info* host_controller; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  HV_PCI_TSBID (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  IO_PAGE_SIZE ; 
 unsigned long iommu_num_pages (unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,unsigned long,unsigned long) ; 
 unsigned long pci_sun4v_iommu_demap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dma_4v_unmap_sg(struct device *dev, struct scatterlist *sglist,
			    int nelems, enum dma_data_direction direction,
			    struct dma_attrs *attrs)
{
	struct pci_pbm_info *pbm;
	struct scatterlist *sg;
	struct iommu *iommu;
	unsigned long flags;
	u32 devhandle;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	devhandle = pbm->devhandle;
	
	spin_lock_irqsave(&iommu->lock, flags);

	sg = sglist;
	while (nelems--) {
		dma_addr_t dma_handle = sg->dma_address;
		unsigned int len = sg->dma_length;
		unsigned long npages, entry;

		if (!len)
			break;
		npages = iommu_num_pages(dma_handle, len, IO_PAGE_SIZE);
		iommu_range_free(iommu, dma_handle, npages);

		entry = ((dma_handle - iommu->page_table_map_base) >> IO_PAGE_SHIFT);
		while (npages) {
			unsigned long num;

			num = pci_sun4v_iommu_demap(devhandle, HV_PCI_TSBID(0, entry),
						    npages);
			entry += num;
			npages -= num;
		}

		sg = sg_next(sg);
	}

	spin_unlock_irqrestore(&iommu->lock, flags);
}