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
struct strbuf {scalar_t__ strbuf_ctxflush; int /*<<< orphan*/  strbuf_enabled; } ;
struct iommu {unsigned long page_table_map_base; int /*<<< orphan*/  lock; int /*<<< orphan*/ * page_table; scalar_t__ iommu_ctxflush; } ;
struct TYPE_2__ {struct strbuf* stc; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  iopte_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long IOPTE_CONTEXT ; 
 unsigned long IO_PAGE_ALIGN (unsigned long) ; 
 unsigned long IO_PAGE_MASK ; 
 unsigned long IO_PAGE_SHIFT ; 
 unsigned long iopte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strbuf_flush (struct strbuf*,struct iommu*,unsigned long,unsigned long,unsigned long,int) ; 

__attribute__((used)) static void dma_4u_sync_single_for_cpu(struct device *dev,
				       dma_addr_t bus_addr, size_t sz,
				       enum dma_data_direction direction)
{
	struct iommu *iommu;
	struct strbuf *strbuf;
	unsigned long flags, ctx, npages;

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	if (!strbuf->strbuf_enabled)
		return;

	spin_lock_irqsave(&iommu->lock, flags);

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	bus_addr &= IO_PAGE_MASK;

	/* Step 1: Record the context, if any. */
	ctx = 0;
	if (iommu->iommu_ctxflush &&
	    strbuf->strbuf_ctxflush) {
		iopte_t *iopte;

		iopte = iommu->page_table +
			((bus_addr - iommu->page_table_map_base)>>IO_PAGE_SHIFT);
		ctx = (iopte_val(*iopte) & IOPTE_CONTEXT) >> 47UL;
	}

	/* Step 2: Kick data out of streaming buffers. */
	strbuf_flush(strbuf, iommu, bus_addr, ctx, npages, direction);

	spin_unlock_irqrestore(&iommu->lock, flags);
}