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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_omap_host {int dma_in_use; int use_dma; unsigned int sg_len; int total_bytes_left; scalar_t__ dma_done; scalar_t__ brs_received; int /*<<< orphan*/  mmc; scalar_t__ sg_idx; struct mmc_data* data; } ;
struct mmc_data {int blksz; int blocks; int sg_len; int flags; TYPE_1__* sg; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLEN ; 
 int /*<<< orphan*/  BUF ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  NBLK ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_omap_get_dma_channel (struct mmc_omap_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_omap_prepare_dma (struct mmc_omap_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_omap_sg_to_buf (struct mmc_omap_host*) ; 
 int /*<<< orphan*/  set_cmd_timeout (struct mmc_omap_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  set_data_timeout (struct mmc_omap_host*,struct mmc_request*) ; 

__attribute__((used)) static void
mmc_omap_prepare_data(struct mmc_omap_host *host, struct mmc_request *req)
{
	struct mmc_data *data = req->data;
	int i, use_dma, block_size;
	unsigned sg_len;

	host->data = data;
	if (data == NULL) {
		OMAP_MMC_WRITE(host, BLEN, 0);
		OMAP_MMC_WRITE(host, NBLK, 0);
		OMAP_MMC_WRITE(host, BUF, 0);
		host->dma_in_use = 0;
		set_cmd_timeout(host, req);
		return;
	}

	block_size = data->blksz;

	OMAP_MMC_WRITE(host, NBLK, data->blocks - 1);
	OMAP_MMC_WRITE(host, BLEN, block_size - 1);
	set_data_timeout(host, req);

	/* cope with calling layer confusion; it issues "single
	 * block" writes using multi-block scatterlists.
	 */
	sg_len = (data->blocks == 1) ? 1 : data->sg_len;

	/* Only do DMA for entire blocks */
	use_dma = host->use_dma;
	if (use_dma) {
		for (i = 0; i < sg_len; i++) {
			if ((data->sg[i].length % block_size) != 0) {
				use_dma = 0;
				break;
			}
		}
	}

	host->sg_idx = 0;
	if (use_dma) {
		if (mmc_omap_get_dma_channel(host, data) == 0) {
			enum dma_data_direction dma_data_dir;

			if (data->flags & MMC_DATA_WRITE)
				dma_data_dir = DMA_TO_DEVICE;
			else
				dma_data_dir = DMA_FROM_DEVICE;

			host->sg_len = dma_map_sg(mmc_dev(host->mmc), data->sg,
						sg_len, dma_data_dir);
			host->total_bytes_left = 0;
			mmc_omap_prepare_dma(host, req->data);
			host->brs_received = 0;
			host->dma_done = 0;
			host->dma_in_use = 1;
		} else
			use_dma = 0;
	}

	/* Revert to PIO? */
	if (!use_dma) {
		OMAP_MMC_WRITE(host, BUF, 0x1f1f);
		host->total_bytes_left = data->blocks * block_size;
		host->sg_len = sg_len;
		mmc_omap_sg_to_buf(host);
		host->dma_in_use = 0;
	}
}