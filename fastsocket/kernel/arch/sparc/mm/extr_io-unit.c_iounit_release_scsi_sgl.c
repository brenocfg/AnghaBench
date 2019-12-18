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
struct scatterlist {int dma_address; int length; } ;
struct iounit_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  bmap; } ;
struct TYPE_2__ {struct iounit_struct* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOD (char*) ; 
 int IOUNIT_DMA_BASE ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iounit_release_scsi_sgl(struct device *dev, struct scatterlist *sg, int sz)
{
	struct iounit_struct *iounit = dev->archdata.iommu;
	unsigned long flags;
	unsigned long vaddr, len;

	spin_lock_irqsave(&iounit->lock, flags);
	while (sz != 0) {
		--sz;
		len = ((sg->dma_address & ~PAGE_MASK) + sg->length + (PAGE_SIZE-1)) >> PAGE_SHIFT;
		vaddr = (sg->dma_address - IOUNIT_DMA_BASE) >> PAGE_SHIFT;
		IOD(("iounit_release %08lx-%08lx\n", (long)vaddr, (long)len+vaddr));
		for (len += vaddr; vaddr < len; vaddr++)
			clear_bit(vaddr, iounit->bmap);
		sg = sg_next(sg);
	}
	spin_unlock_irqrestore(&iounit->lock, flags);
}