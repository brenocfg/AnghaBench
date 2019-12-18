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
struct s3cmci_host {int dmatogo; int /*<<< orphan*/  dma; scalar_t__ dma_complete; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int flags; int /*<<< orphan*/ * sg; int /*<<< orphan*/  sg_len; } ;

/* Variables and functions */
 int BOTH_DIR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  S3C2410_DMAOP_FLUSH ; 
 int /*<<< orphan*/  S3C2410_DMAOP_START ; 
 int /*<<< orphan*/  S3C2410_DMASRC_HW ; 
 int /*<<< orphan*/  S3C2410_DMASRC_MEM ; 
 int /*<<< orphan*/  dbg (struct s3cmci_host*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_dma ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_dma_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s3c2410_dma_enqueue (int /*<<< orphan*/ ,struct s3cmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3cmci_dma_setup (struct s3cmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3cmci_prepare_dma(struct s3cmci_host *host, struct mmc_data *data)
{
	int dma_len, i;
	int rw = data->flags & MMC_DATA_WRITE;

	BUG_ON((data->flags & BOTH_DIR) == BOTH_DIR);

	s3cmci_dma_setup(host, rw ? S3C2410_DMASRC_MEM : S3C2410_DMASRC_HW);
	s3c2410_dma_ctrl(host->dma, S3C2410_DMAOP_FLUSH);

	dma_len = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			     rw ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

	if (dma_len == 0)
		return -ENOMEM;

	host->dma_complete = 0;
	host->dmatogo = dma_len;

	for (i = 0; i < dma_len; i++) {
		int res;

		dbg(host, dbg_dma, "enqueue %i: %08x@%u\n", i,
		    sg_dma_address(&data->sg[i]),
		    sg_dma_len(&data->sg[i]));

		res = s3c2410_dma_enqueue(host->dma, host,
					  sg_dma_address(&data->sg[i]),
					  sg_dma_len(&data->sg[i]));

		if (res) {
			s3c2410_dma_ctrl(host->dma, S3C2410_DMAOP_FLUSH);
			return -EBUSY;
		}
	}

	s3c2410_dma_ctrl(host->dma, S3C2410_DMAOP_START);

	return 0;
}