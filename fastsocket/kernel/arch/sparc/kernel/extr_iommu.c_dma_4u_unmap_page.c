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
struct iommu {unsigned long page_table_map_base; int /*<<< orphan*/  lock; scalar_t__ iommu_ctxflush; int /*<<< orphan*/ * page_table; } ;
struct dma_attrs {int dummy; } ;
struct TYPE_2__ {struct strbuf* stc; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  iopte_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int DMA_NONE ; 
 unsigned long IOPTE_CONTEXT ; 
 unsigned long IO_PAGE_ALIGN (unsigned long) ; 
 unsigned long IO_PAGE_MASK ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_free_ctx (struct iommu*,unsigned long) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iopte_make_dummy (struct iommu*,int /*<<< orphan*/ *) ; 
 unsigned long iopte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strbuf_flush (struct strbuf*,struct iommu*,unsigned long,unsigned long,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dma_4u_unmap_page(struct device *dev, dma_addr_t bus_addr,
			      size_t sz, enum dma_data_direction direction,
			      struct dma_attrs *attrs)
{
	struct iommu *iommu;
	struct strbuf *strbuf;
	iopte_t *base;
	unsigned long flags, npages, ctx, i;

	if (unlikely(direction == DMA_NONE)) {
		if (printk_ratelimit())
			WARN_ON(1);
		return;
	}

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	base = iommu->page_table +
		((bus_addr - iommu->page_table_map_base) >> IO_PAGE_SHIFT);
	bus_addr &= IO_PAGE_MASK;

	spin_lock_irqsave(&iommu->lock, flags);

	/* Record the context, if any. */
	ctx = 0;
	if (iommu->iommu_ctxflush)
		ctx = (iopte_val(*base) & IOPTE_CONTEXT) >> 47UL;

	/* Step 1: Kick data out of streaming buffers if necessary. */
	if (strbuf->strbuf_enabled)
		strbuf_flush(strbuf, iommu, bus_addr, ctx,
			     npages, direction);

	/* Step 2: Clear out TSB entries. */
	for (i = 0; i < npages; i++)
		iopte_make_dummy(iommu, base + i);

	iommu_range_free(iommu, bus_addr, npages);

	iommu_free_ctx(iommu, ctx);

	spin_unlock_irqrestore(&iommu->lock, flags);
}