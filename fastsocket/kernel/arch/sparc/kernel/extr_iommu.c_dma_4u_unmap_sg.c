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
struct strbuf {scalar_t__ strbuf_enabled; } ;
struct scatterlist {unsigned int dma_length; int /*<<< orphan*/  dma_address; } ;
struct iommu {unsigned long page_table_map_base; int /*<<< orphan*/  lock; int /*<<< orphan*/ * page_table; } ;
struct dma_attrs {int dummy; } ;
struct TYPE_2__ {struct strbuf* stc; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  iopte_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  IO_PAGE_MASK ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  IO_PAGE_SIZE ; 
 unsigned long fetch_sg_ctx (struct iommu*,struct scatterlist*) ; 
 int /*<<< orphan*/  iommu_free_ctx (struct iommu*,unsigned long) ; 
 unsigned long iommu_num_pages (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iopte_make_dummy (struct iommu*,int /*<<< orphan*/ *) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strbuf_flush (struct strbuf*,struct iommu*,int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 

__attribute__((used)) static void dma_4u_unmap_sg(struct device *dev, struct scatterlist *sglist,
			    int nelems, enum dma_data_direction direction,
			    struct dma_attrs *attrs)
{
	unsigned long flags, ctx;
	struct scatterlist *sg;
	struct strbuf *strbuf;
	struct iommu *iommu;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	ctx = fetch_sg_ctx(iommu, sglist);

	spin_lock_irqsave(&iommu->lock, flags);

	sg = sglist;
	while (nelems--) {
		dma_addr_t dma_handle = sg->dma_address;
		unsigned int len = sg->dma_length;
		unsigned long npages, entry;
		iopte_t *base;
		int i;

		if (!len)
			break;
		npages = iommu_num_pages(dma_handle, len, IO_PAGE_SIZE);
		iommu_range_free(iommu, dma_handle, npages);

		entry = ((dma_handle - iommu->page_table_map_base)
			 >> IO_PAGE_SHIFT);
		base = iommu->page_table + entry;

		dma_handle &= IO_PAGE_MASK;
		if (strbuf->strbuf_enabled)
			strbuf_flush(strbuf, iommu, dma_handle, ctx,
				     npages, direction);

		for (i = 0; i < npages; i++)
			iopte_make_dummy(iommu, base + i);

		sg = sg_next(sg);
	}

	iommu_free_ctx(iommu, ctx);

	spin_unlock_irqrestore(&iommu->lock, flags);
}