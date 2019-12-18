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
struct tusb_omap_dma_ch {struct tusb_omap_dma* tusb_dma; } ;
struct tusb_omap_dma {int ch; int dmareq; int sync_dev; int /*<<< orphan*/  multichannel; } ;
struct dma_channel {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DMA_STATUS_FREE ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 
 int /*<<< orphan*/  omap_stop_dma (int) ; 
 struct tusb_omap_dma_ch* to_chdat (struct dma_channel*) ; 

__attribute__((used)) static int tusb_omap_dma_abort(struct dma_channel *channel)
{
	struct tusb_omap_dma_ch	*chdat = to_chdat(channel);
	struct tusb_omap_dma	*tusb_dma = chdat->tusb_dma;

	if (!tusb_dma->multichannel) {
		if (tusb_dma->ch >= 0) {
			omap_stop_dma(tusb_dma->ch);
			omap_free_dma(tusb_dma->ch);
			tusb_dma->ch = -1;
		}

		tusb_dma->dmareq = -1;
		tusb_dma->sync_dev = -1;
	}

	channel->status = MUSB_DMA_STATUS_FREE;

	return 0;
}