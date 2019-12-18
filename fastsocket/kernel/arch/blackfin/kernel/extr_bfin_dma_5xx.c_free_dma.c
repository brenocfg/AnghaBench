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
struct TYPE_2__ {scalar_t__ chan_status; int /*<<< orphan*/  dmalock; int /*<<< orphan*/  data; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DMA_CHANNEL_FREE ; 
 unsigned int MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/  clear_dma_buffer (unsigned int) ; 
 int /*<<< orphan*/  disable_dma (unsigned int) ; 
 TYPE_1__* dma_ch ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void free_dma(unsigned int channel)
{
	pr_debug("freedma() : BEGIN \n");
	BUG_ON(channel >= MAX_DMA_CHANNELS ||
			dma_ch[channel].chan_status == DMA_CHANNEL_FREE);

	/* Halt the DMA */
	disable_dma(channel);
	clear_dma_buffer(channel);

	if (dma_ch[channel].irq)
		free_irq(dma_ch[channel].irq, dma_ch[channel].data);

	/* Clear the DMA Variable in the Channel */
	mutex_lock(&(dma_ch[channel].dmalock));
	dma_ch[channel].chan_status = DMA_CHANNEL_FREE;
	mutex_unlock(&(dma_ch[channel].dmalock));

	pr_debug("freedma() : END \n");
}