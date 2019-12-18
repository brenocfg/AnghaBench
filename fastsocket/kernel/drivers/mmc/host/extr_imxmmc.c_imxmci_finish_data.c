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
struct mmc_data {int error; int /*<<< orphan*/  bytes_xfered; int /*<<< orphan*/  sg; } ;
struct imxmci_host {struct mmc_data* data; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  mmc; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dma_nents; int /*<<< orphan*/  dma; int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IMXMCI_PEND_DMA_DATA_b ; 
 unsigned int STATUS_CRC_READ_ERR ; 
 unsigned int STATUS_CRC_WRITE_ERR ; 
 unsigned int STATUS_ERR_MASK ; 
 unsigned int STATUS_TIME_OUT_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_dma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imxmci_finish_data(struct imxmci_host *host, unsigned int stat)
{
	struct mmc_data *data = host->data;
	int data_error;

	if (test_and_clear_bit(IMXMCI_PEND_DMA_DATA_b, &host->pending_events)) {
		imx_dma_disable(host->dma);
		dma_unmap_sg(mmc_dev(host->mmc), data->sg, host->dma_nents,
			     host->dma_dir);
	}

	if (stat & STATUS_ERR_MASK) {
		dev_dbg(mmc_dev(host->mmc), "request failed. status: 0x%08x\n", stat);
		if (stat & (STATUS_CRC_READ_ERR | STATUS_CRC_WRITE_ERR))
			data->error = -EILSEQ;
		else if (stat & STATUS_TIME_OUT_READ)
			data->error = -ETIMEDOUT;
		else
			data->error = -EIO;
	} else {
		data->bytes_xfered = host->dma_size;
	}

	data_error = data->error;

	host->data = NULL;

	return data_error;
}