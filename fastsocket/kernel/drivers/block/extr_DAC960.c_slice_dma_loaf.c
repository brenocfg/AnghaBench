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
struct dma_loaf {void* cpu_base; int length; size_t dma_free; void* cpu_free; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void *slice_dma_loaf(struct dma_loaf *loaf, size_t len,
					dma_addr_t *dma_handle)
{
	void *cpu_end = loaf->cpu_free + len;
	void *cpu_addr = loaf->cpu_free;

	BUG_ON(cpu_end > loaf->cpu_base + loaf->length);
	*dma_handle = loaf->dma_free;
	loaf->cpu_free = cpu_end;
	loaf->dma_free += len;
	return cpu_addr;
}