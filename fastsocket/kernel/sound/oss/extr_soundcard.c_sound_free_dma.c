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
 scalar_t__ DMA_MAP_UNAVAIL ; 
 scalar_t__* dma_alloc_map ; 
 int /*<<< orphan*/  free_dma (int) ; 

void sound_free_dma(int chn)
{
	if (dma_alloc_map[chn] == DMA_MAP_UNAVAIL) {
		/* printk( "sound_free_dma: Bad access to DMA channel %d\n",  chn); */
		return;
	}
	free_dma(chn);
	dma_alloc_map[chn] = DMA_MAP_UNAVAIL;
}