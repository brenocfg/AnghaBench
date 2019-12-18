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
struct mmc_omap_host {int dma_ch; int dma_is_read; scalar_t__ id; int /*<<< orphan*/  mmc; int /*<<< orphan*/  dma_timer; } ;
struct mmc_data {int flags; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int OMAP_DMA_MMC2_RX ; 
 int OMAP_DMA_MMC2_TX ; 
 int OMAP_DMA_MMC_RX ; 
 int OMAP_DMA_MMC_TX ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_dma_cb ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 
 int omap_request_dma (int,char const*,int /*<<< orphan*/ ,struct mmc_omap_host*,int*) ; 

__attribute__((used)) static int mmc_omap_get_dma_channel(struct mmc_omap_host *host, struct mmc_data *data)
{
	const char *dma_dev_name;
	int sync_dev, dma_ch, is_read, r;

	is_read = !(data->flags & MMC_DATA_WRITE);
	del_timer_sync(&host->dma_timer);
	if (host->dma_ch >= 0) {
		if (is_read == host->dma_is_read)
			return 0;
		omap_free_dma(host->dma_ch);
		host->dma_ch = -1;
	}

	if (is_read) {
		if (host->id == 0) {
			sync_dev = OMAP_DMA_MMC_RX;
			dma_dev_name = "MMC1 read";
		} else {
			sync_dev = OMAP_DMA_MMC2_RX;
			dma_dev_name = "MMC2 read";
		}
	} else {
		if (host->id == 0) {
			sync_dev = OMAP_DMA_MMC_TX;
			dma_dev_name = "MMC1 write";
		} else {
			sync_dev = OMAP_DMA_MMC2_TX;
			dma_dev_name = "MMC2 write";
		}
	}
	r = omap_request_dma(sync_dev, dma_dev_name, mmc_omap_dma_cb,
			     host, &dma_ch);
	if (r != 0) {
		dev_dbg(mmc_dev(host->mmc), "omap_request_dma() failed with %d\n", r);
		return r;
	}
	host->dma_ch = dma_ch;
	host->dma_is_read = is_read;

	return 0;
}