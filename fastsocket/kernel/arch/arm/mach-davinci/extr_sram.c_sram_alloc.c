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
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {unsigned long sram_dma; } ;

/* Variables and functions */
 unsigned long SRAM_VIRT ; 
 TYPE_1__ davinci_soc_info ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sram_pool ; 

void *sram_alloc(size_t len, dma_addr_t *dma)
{
	unsigned long vaddr;
	dma_addr_t dma_base = davinci_soc_info.sram_dma;

	if (dma)
		*dma = 0;
	if (!sram_pool || (dma && !dma_base))
		return NULL;

	vaddr = gen_pool_alloc(sram_pool, len);
	if (!vaddr)
		return NULL;

	if (dma)
		*dma = dma_base + (vaddr - SRAM_VIRT);
	return (void *)vaddr;

}