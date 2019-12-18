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
struct mmc_omap_host {scalar_t__ dma_ch; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  mmc; int /*<<< orphan*/  dma_timer; } ;
struct mmc_data {int flags; int /*<<< orphan*/  sg; scalar_t__ error; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ HZ ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  omap_stop_dma (scalar_t__) ; 

__attribute__((used)) static void
mmc_omap_release_dma(struct mmc_omap_host *host, struct mmc_data *data,
		     int abort)
{
	enum dma_data_direction dma_data_dir;

	BUG_ON(host->dma_ch < 0);
	if (data->error)
		omap_stop_dma(host->dma_ch);
	/* Release DMA channel lazily */
	mod_timer(&host->dma_timer, jiffies + HZ);
	if (data->flags & MMC_DATA_WRITE)
		dma_data_dir = DMA_TO_DEVICE;
	else
		dma_data_dir = DMA_FROM_DEVICE;
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, host->sg_len,
		     dma_data_dir);
}