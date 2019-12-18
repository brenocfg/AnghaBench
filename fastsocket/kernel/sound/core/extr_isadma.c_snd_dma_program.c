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

/* Variables and functions */
 unsigned short DMA_MODE_NO_ENABLE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (unsigned long) ; 
 int /*<<< orphan*/  disable_dma (unsigned long) ; 
 int /*<<< orphan*/  enable_dma (unsigned long) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_dma_count (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  set_dma_mode (unsigned long,unsigned short) ; 

void snd_dma_program(unsigned long dma,
		     unsigned long addr, unsigned int size,
                     unsigned short mode)
{
	unsigned long flags;

	flags = claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma, mode);
	set_dma_addr(dma, addr);
	set_dma_count(dma, size);
	if (!(mode & DMA_MODE_NO_ENABLE))
		enable_dma(dma);
	release_dma_lock(flags);
}