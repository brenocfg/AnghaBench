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
struct frv_dma_channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRV_DMA_FLAGS_INUSE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct frv_dma_channel*) ; 
 struct frv_dma_channel* frv_dma_channels ; 
 int /*<<< orphan*/  frv_dma_channels_lock ; 
 int /*<<< orphan*/  frv_dma_stop (int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void frv_dma_close(int dma)
{
	struct frv_dma_channel *channel = &frv_dma_channels[dma];
	unsigned long flags;

	write_lock_irqsave(&frv_dma_channels_lock, flags);

	free_irq(channel->irq, channel);
	frv_dma_stop(dma);

	channel->flags &= ~FRV_DMA_FLAGS_INUSE;

	write_unlock_irqrestore(&frv_dma_channels_lock, flags);
}