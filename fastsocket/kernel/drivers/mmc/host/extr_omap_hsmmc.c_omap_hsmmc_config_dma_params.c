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
struct scatterlist {int dummy; } ;
struct omap_hsmmc_host {int dma_ch; TYPE_1__* data; scalar_t__ mapbase; } ;
struct mmc_data {int flags; } ;
struct TYPE_2__ {int blksz; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  OMAP_DMA_AMODE_CONSTANT ; 
 int /*<<< orphan*/  OMAP_DMA_AMODE_POST_INC ; 
 int /*<<< orphan*/  OMAP_DMA_DATA_TYPE_S32 ; 
 int /*<<< orphan*/  OMAP_DMA_SYNC_FRAME ; 
 scalar_t__ OMAP_HSMMC_DATA ; 
 int /*<<< orphan*/  omap_hsmmc_get_dma_sync_dev (struct omap_hsmmc_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  omap_set_dma_dest_params (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_src_params (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_transfer_params (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_start_dma (int) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void omap_hsmmc_config_dma_params(struct omap_hsmmc_host *host,
				       struct mmc_data *data,
				       struct scatterlist *sgl)
{
	int blksz, nblk, dma_ch;

	dma_ch = host->dma_ch;
	if (data->flags & MMC_DATA_WRITE) {
		omap_set_dma_dest_params(dma_ch, 0, OMAP_DMA_AMODE_CONSTANT,
			(host->mapbase + OMAP_HSMMC_DATA), 0, 0);
		omap_set_dma_src_params(dma_ch, 0, OMAP_DMA_AMODE_POST_INC,
			sg_dma_address(sgl), 0, 0);
	} else {
		omap_set_dma_src_params(dma_ch, 0, OMAP_DMA_AMODE_CONSTANT,
			(host->mapbase + OMAP_HSMMC_DATA), 0, 0);
		omap_set_dma_dest_params(dma_ch, 0, OMAP_DMA_AMODE_POST_INC,
			sg_dma_address(sgl), 0, 0);
	}

	blksz = host->data->blksz;
	nblk = sg_dma_len(sgl) / blksz;

	omap_set_dma_transfer_params(dma_ch, OMAP_DMA_DATA_TYPE_S32,
			blksz / 4, nblk, OMAP_DMA_SYNC_FRAME,
			omap_hsmmc_get_dma_sync_dev(host, data),
			!(data->flags & MMC_DATA_WRITE));

	omap_start_dma(dma_ch);
}