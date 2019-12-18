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
struct scatterlist {int length; int offset; int dma_address; int dma_length; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int iommu_get_one (struct device*,int /*<<< orphan*/ ,int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void iommu_get_scsi_sgl_noflush(struct device *dev, struct scatterlist *sg, int sz)
{
	int n;

	while (sz != 0) {
		--sz;
		n = (sg->length + sg->offset + PAGE_SIZE-1) >> PAGE_SHIFT;
		sg->dma_address = iommu_get_one(dev, sg_page(sg), n) + sg->offset;
		sg->dma_length = sg->length;
		sg = sg_next(sg);
	}
}