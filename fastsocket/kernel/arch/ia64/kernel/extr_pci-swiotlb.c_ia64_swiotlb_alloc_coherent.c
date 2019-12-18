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
struct device {scalar_t__ coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_DMA ; 
 void* swiotlb_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ia64_swiotlb_alloc_coherent(struct device *dev, size_t size,
					 dma_addr_t *dma_handle, gfp_t gfp)
{
	if (dev->coherent_dma_mask != DMA_BIT_MASK(64))
		gfp |= GFP_DMA;
	return swiotlb_alloc_coherent(dev, size, dma_handle, gfp);
}