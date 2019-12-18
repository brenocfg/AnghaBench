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
typedef  int u64 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_DMA ; 
 int get_coherent_dma_mask (struct device*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_dma (struct device*,void*) ; 

__attribute__((used)) static void *
__dma_alloc(struct device *dev, size_t size, dma_addr_t *handle, gfp_t gfp,
	    pgprot_t prot)
{
	void *virt;
	u64 mask = get_coherent_dma_mask(dev);

	if (!mask)
		goto error;

	if (mask < 0xffffffffULL)
		gfp |= GFP_DMA;
	virt = kmalloc(size, gfp);
	if (!virt)
		goto error;

	*handle =  virt_to_dma(dev, virt);
	return virt;

error:
	*handle = ~0;
	return NULL;
}