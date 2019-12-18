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
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  dma_length; int /*<<< orphan*/  dma_address; } ;
struct iounit_struct {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct iounit_struct* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounit_get_area (struct iounit_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iounit_get_scsi_sgl(struct device *dev, struct scatterlist *sg, int sz)
{
	struct iounit_struct *iounit = dev->archdata.iommu;
	unsigned long flags;

	/* FIXME: Cache some resolved pages - often several sg entries are to the same page */
	spin_lock_irqsave(&iounit->lock, flags);
	while (sz != 0) {
		--sz;
		sg->dma_address = iounit_get_area(iounit, (unsigned long) sg_virt(sg), sg->length);
		sg->dma_length = sg->length;
		sg = sg_next(sg);
	}
	spin_unlock_irqrestore(&iounit->lock, flags);
}