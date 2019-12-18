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
struct talitos_edesc {int src_nents; int dst_nents; scalar_t__ src_is_chained; scalar_t__ dst_is_chained; } ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talitos_unmap_sg_chain (struct device*,struct scatterlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void talitos_sg_unmap(struct device *dev,
			     struct talitos_edesc *edesc,
			     struct scatterlist *src,
			     struct scatterlist *dst)
{
	unsigned int src_nents = edesc->src_nents ? : 1;
	unsigned int dst_nents = edesc->dst_nents ? : 1;

	if (src != dst) {
		if (edesc->src_is_chained)
			talitos_unmap_sg_chain(dev, src, DMA_TO_DEVICE);
		else
			dma_unmap_sg(dev, src, src_nents, DMA_TO_DEVICE);

		if (edesc->dst_is_chained)
			talitos_unmap_sg_chain(dev, dst, DMA_FROM_DEVICE);
		else
			dma_unmap_sg(dev, dst, dst_nents, DMA_FROM_DEVICE);
	} else
		if (edesc->src_is_chained)
			talitos_unmap_sg_chain(dev, src, DMA_BIDIRECTIONAL);
		else
			dma_unmap_sg(dev, src, src_nents, DMA_BIDIRECTIONAL);
}