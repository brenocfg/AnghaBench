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
struct scatterlist {int dma_address; int length; int /*<<< orphan*/  offset; } ;
struct mmc_data {scalar_t__ sg_len; int blksz; struct scatterlist* sg; } ;
struct mmc_command {struct mmc_data* data; } ;
struct at91mci_host {scalar_t__ transfer_index; struct mmc_command* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_RCR ; 
 int /*<<< orphan*/  ATMEL_PDC_RNCR ; 
 int /*<<< orphan*/  ATMEL_PDC_RNPR ; 
 int /*<<< orphan*/  ATMEL_PDC_RPR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ at91_mci_read (struct at91mci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int) ; 
 int dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void at91_mci_pre_dma_read(struct at91mci_host *host)
{
	int i;
	struct scatterlist *sg;
	struct mmc_command *cmd;
	struct mmc_data *data;

	pr_debug("pre dma read\n");

	cmd = host->cmd;
	if (!cmd) {
		pr_debug("no command\n");
		return;
	}

	data = cmd->data;
	if (!data) {
		pr_debug("no data\n");
		return;
	}

	for (i = 0; i < 2; i++) {
		/* nothing left to transfer */
		if (host->transfer_index >= data->sg_len) {
			pr_debug("Nothing left to transfer (index = %d)\n", host->transfer_index);
			break;
		}

		/* Check to see if this needs filling */
		if (i == 0) {
			if (at91_mci_read(host, ATMEL_PDC_RCR) != 0) {
				pr_debug("Transfer active in current\n");
				continue;
			}
		}
		else {
			if (at91_mci_read(host, ATMEL_PDC_RNCR) != 0) {
				pr_debug("Transfer active in next\n");
				continue;
			}
		}

		/* Setup the next transfer */
		pr_debug("Using transfer index %d\n", host->transfer_index);

		sg = &data->sg[host->transfer_index++];
		pr_debug("sg = %p\n", sg);

		sg->dma_address = dma_map_page(NULL, sg_page(sg), sg->offset, sg->length, DMA_FROM_DEVICE);

		pr_debug("dma address = %08X, length = %d\n", sg->dma_address, sg->length);

		if (i == 0) {
			at91_mci_write(host, ATMEL_PDC_RPR, sg->dma_address);
			at91_mci_write(host, ATMEL_PDC_RCR, (data->blksz & 0x3) ? sg->length : sg->length / 4);
		}
		else {
			at91_mci_write(host, ATMEL_PDC_RNPR, sg->dma_address);
			at91_mci_write(host, ATMEL_PDC_RNCR, (data->blksz & 0x3) ? sg->length : sg->length / 4);
		}
	}

	pr_debug("pre dma read done\n");
}