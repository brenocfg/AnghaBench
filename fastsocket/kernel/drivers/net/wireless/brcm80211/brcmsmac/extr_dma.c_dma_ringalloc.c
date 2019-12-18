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
typedef  int uint ;
typedef  int u32 ;
typedef  int u16 ;
struct dma_info {int /*<<< orphan*/  dmadev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int dma_align_sizetobits (int) ; 
 void* dma_alloc_consistent (struct dma_info*,int,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (unsigned long,int) ; 

__attribute__((used)) static void *dma_ringalloc(struct dma_info *di, u32 boundary, uint size,
			   u16 *alignbits, uint *alloced,
			   dma_addr_t *descpa)
{
	void *va;
	u32 desc_strtaddr;
	u32 alignbytes = 1 << *alignbits;

	va = dma_alloc_consistent(di, size, *alignbits, alloced, descpa);

	if (NULL == va)
		return NULL;

	desc_strtaddr = (u32) roundup((unsigned long)va, alignbytes);
	if (((desc_strtaddr + size - 1) & boundary) != (desc_strtaddr
							& boundary)) {
		*alignbits = dma_align_sizetobits(size);
		dma_free_coherent(di->dmadev, size, va, *descpa);
		va = dma_alloc_consistent(di, size, *alignbits,
			alloced, descpa);
	}
	return va;
}