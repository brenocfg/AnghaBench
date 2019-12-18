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
typedef  int /*<<< orphan*/  u32 ;
struct omap24xxcam_dma {int free_dmach; int next_dmach; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; TYPE_1__* ch_state; int /*<<< orphan*/  dma_stop; } ;
typedef  int /*<<< orphan*/  dma_callback_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {void* arg; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int EBUSY ; 
 int NUM_CAMDMA_CHANNELS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_dmahw_transfer_chain (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  omap24xxcam_dmahw_transfer_setup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_dmahw_transfer_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int omap24xxcam_dma_start(struct omap24xxcam_dma *dma, dma_addr_t start,
				 u32 len, dma_callback_t callback, void *arg)
{
	unsigned long flags;
	int dmach;

	spin_lock_irqsave(&dma->lock, flags);

	if (!dma->free_dmach || atomic_read(&dma->dma_stop)) {
		spin_unlock_irqrestore(&dma->lock, flags);
		return -EBUSY;
	}

	dmach = dma->next_dmach;

	dma->ch_state[dmach].callback = callback;
	dma->ch_state[dmach].arg = arg;

	omap24xxcam_dmahw_transfer_setup(dma->base, dmach, start, len);

	/* We're ready to start the DMA transfer. */

	if (dma->free_dmach < NUM_CAMDMA_CHANNELS) {
		/* A transfer is already in progress, so try to chain to it. */
		omap24xxcam_dmahw_transfer_chain(dma->base, dmach,
						 dma->free_dmach);
	} else {
		/* No transfer is in progress, so we'll just start this one
		 * now.
		 */
		omap24xxcam_dmahw_transfer_start(dma->base, dmach);
	}

	dma->next_dmach = (dma->next_dmach + 1) % NUM_CAMDMA_CHANNELS;
	dma->free_dmach--;

	spin_unlock_irqrestore(&dma->lock, flags);

	return 0;
}