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
typedef  int /*<<< orphan*/  DMA_MemType_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TYPE_DMA ; 
 int /*<<< orphan*/  DMA_MEM_TYPE_KMALLOC ; 
 int /*<<< orphan*/  DMA_MEM_TYPE_USER ; 
 int /*<<< orphan*/  DMA_MEM_TYPE_VMALLOC ; 
 unsigned long PAGE_OFFSET ; 
 unsigned long VMALLOC_END ; 
 scalar_t__ is_vmalloc_addr (void*) ; 

DMA_MemType_t dma_mem_type(void *addr)
{
	unsigned long addrVal = (unsigned long)addr;

	if (addrVal >= VMALLOC_END) {
		/* NOTE: DMA virtual memory space starts at 0xFFxxxxxx */

		/* dma_alloc_xxx pages are physically and virtually contiguous */

		return DMA_MEM_TYPE_DMA;
	}

	/* Technically, we could add one more classification. Addresses between VMALLOC_END */
	/* and the beginning of the DMA virtual address could be considered to be I/O space. */
	/* Right now, nobody cares about this particular classification, so we ignore it. */

	if (is_vmalloc_addr(addr)) {
		/* Address comes from the vmalloc'd region. Pages are virtually */
		/* contiguous but NOT physically contiguous */

		return DMA_MEM_TYPE_VMALLOC;
	}

	if (addrVal >= PAGE_OFFSET) {
		/* PAGE_OFFSET is typically 0xC0000000 */

		/* kmalloc'd pages are physically contiguous */

		return DMA_MEM_TYPE_KMALLOC;
	}

	return DMA_MEM_TYPE_USER;
}