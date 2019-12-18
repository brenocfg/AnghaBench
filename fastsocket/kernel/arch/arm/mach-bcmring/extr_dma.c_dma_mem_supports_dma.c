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
typedef  scalar_t__ DMA_MemType_t ;

/* Variables and functions */
 scalar_t__ DMA_MEM_TYPE_DMA ; 
 scalar_t__ DMA_MEM_TYPE_KMALLOC ; 
 scalar_t__ DMA_MEM_TYPE_USER ; 
 scalar_t__ dma_mem_type (void*) ; 

int dma_mem_supports_dma(void *addr)
{
	DMA_MemType_t memType = dma_mem_type(addr);

	return (memType == DMA_MEM_TYPE_DMA)
#if ALLOW_MAP_OF_KMALLOC_MEMORY
	    || (memType == DMA_MEM_TYPE_KMALLOC)
#endif
	    || (memType == DMA_MEM_TYPE_USER);
}