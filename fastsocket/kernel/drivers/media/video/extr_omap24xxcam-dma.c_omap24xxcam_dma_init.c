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
struct omap24xxcam_dma {unsigned long base; int free_dmach; TYPE_1__* ch_state; scalar_t__ next_dmach; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int NUM_CAMDMA_CHANNELS ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap24xxcam_dma_init(struct omap24xxcam_dma *dma,
				 unsigned long base)
{
	int ch;

	/* group all channels on DMA IRQ0 and unmask irq */
	spin_lock_init(&dma->lock);
	dma->base = base;
	dma->free_dmach = NUM_CAMDMA_CHANNELS;
	dma->next_dmach = 0;
	for (ch = 0; ch < NUM_CAMDMA_CHANNELS; ch++) {
		dma->ch_state[ch].callback = NULL;
		dma->ch_state[ch].arg = NULL;
	}
}