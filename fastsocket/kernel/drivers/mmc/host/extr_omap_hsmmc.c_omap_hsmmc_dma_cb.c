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
typedef  int u16 ;
struct omap_hsmmc_host {int dma_ch; scalar_t__ dma_sg_idx; scalar_t__ dma_len; int /*<<< orphan*/  sem; TYPE_1__* data; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {scalar_t__ sg; } ;

/* Variables and functions */
 int OMAP2_DMA_MISALIGNED_ERR_IRQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 
 int /*<<< orphan*/  omap_hsmmc_config_dma_params (struct omap_hsmmc_host*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_hsmmc_dma_cb(int lch, u16 ch_status, void *data)
{
	struct omap_hsmmc_host *host = data;

	if (ch_status & OMAP2_DMA_MISALIGNED_ERR_IRQ)
		dev_dbg(mmc_dev(host->mmc), "MISALIGNED_ADRS_ERR\n");

	if (host->dma_ch < 0)
		return;

	host->dma_sg_idx++;
	if (host->dma_sg_idx < host->dma_len) {
		/* Fire up the next transfer. */
		omap_hsmmc_config_dma_params(host, host->data,
					   host->data->sg + host->dma_sg_idx);
		return;
	}

	omap_free_dma(host->dma_ch);
	host->dma_ch = -1;
	/*
	 * DMA Callback: run in interrupt context.
	 * mutex_unlock will throw a kernel warning if used.
	 */
	up(&host->sem);
}