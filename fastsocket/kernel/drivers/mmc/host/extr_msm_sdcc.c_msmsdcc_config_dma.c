#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct scatterlist {int dummy; } ;
struct msmsdcc_nc_dmadata {int cmdptr; TYPE_4__* cmd; } ;
struct TYPE_6__ {int cmdptr; int /*<<< orphan*/  complete_func; } ;
struct TYPE_7__ {unsigned int num_ents; int cmd_busaddr; TYPE_2__ hdr; int /*<<< orphan*/  cmdptr_busaddr; struct scatterlist* sg; int /*<<< orphan*/  dir; struct msmsdcc_nc_dmadata* nc; } ;
struct TYPE_5__ {scalar_t__ user_pages; } ;
struct msmsdcc_host {int pdev_id; TYPE_3__ dma; int /*<<< orphan*/  mmc; TYPE_1__ curr; } ;
struct mmc_data {unsigned int sg_len; int flags; struct scatterlist* sg; } ;
struct TYPE_8__ {int src_dst_len; int row_offset; int num_rows; int /*<<< orphan*/  cmd; void* dst_row_addr; void* src_row_addr; } ;
typedef  TYPE_4__ dmov_box ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CMD_DST_CRCI (int) ; 
 int /*<<< orphan*/  CMD_LC ; 
 int /*<<< orphan*/  CMD_MODE_BOX ; 
 int CMD_PTR_LP ; 
 int /*<<< orphan*/  CMD_SRC_CRCI (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DMOV_CMD_ADDR (int /*<<< orphan*/ ) ; 
 int DMOV_CMD_PTR_LIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int MCI_FIFOSIZE ; 
 int MMC_DATA_READ ; 
 int MSMSDCC_CRCI_SDC1 ; 
 int MSMSDCC_CRCI_SDC2 ; 
 int MSMSDCC_CRCI_SDC3 ; 
 int MSMSDCC_CRCI_SDC4 ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msmsdcc_dma_complete_func ; 
 void* msmsdcc_fifo_addr (struct msmsdcc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 void* sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 int validate_dma (struct msmsdcc_host*,struct mmc_data*) ; 

__attribute__((used)) static int msmsdcc_config_dma(struct msmsdcc_host *host, struct mmc_data *data)
{
	struct msmsdcc_nc_dmadata *nc;
	dmov_box *box;
	uint32_t rows;
	uint32_t crci;
	unsigned int n;
	int i, rc;
	struct scatterlist *sg = data->sg;

	rc = validate_dma(host, data);
	if (rc)
		return rc;

	host->dma.sg = data->sg;
	host->dma.num_ents = data->sg_len;

	nc = host->dma.nc;

	switch (host->pdev_id) {
	case 1:
		crci = MSMSDCC_CRCI_SDC1;
		break;
	case 2:
		crci = MSMSDCC_CRCI_SDC2;
		break;
	case 3:
		crci = MSMSDCC_CRCI_SDC3;
		break;
	case 4:
		crci = MSMSDCC_CRCI_SDC4;
		break;
	default:
		host->dma.sg = NULL;
		host->dma.num_ents = 0;
		return -ENOENT;
	}

	if (data->flags & MMC_DATA_READ)
		host->dma.dir = DMA_FROM_DEVICE;
	else
		host->dma.dir = DMA_TO_DEVICE;

	host->curr.user_pages = 0;

	n = dma_map_sg(mmc_dev(host->mmc), host->dma.sg,
		       host->dma.num_ents, host->dma.dir);

	if (n != host->dma.num_ents) {
		pr_err("%s: Unable to map in all sg elements\n",
		       mmc_hostname(host->mmc));
		host->dma.sg = NULL;
		host->dma.num_ents = 0;
		return -ENOMEM;
	}

	box = &nc->cmd[0];
	for (i = 0; i < host->dma.num_ents; i++) {
		box->cmd = CMD_MODE_BOX;

		if (i == (host->dma.num_ents - 1))
			box->cmd |= CMD_LC;
		rows = (sg_dma_len(sg) % MCI_FIFOSIZE) ?
			(sg_dma_len(sg) / MCI_FIFOSIZE) + 1 :
			(sg_dma_len(sg) / MCI_FIFOSIZE) ;

		if (data->flags & MMC_DATA_READ) {
			box->src_row_addr = msmsdcc_fifo_addr(host);
			box->dst_row_addr = sg_dma_address(sg);

			box->src_dst_len = (MCI_FIFOSIZE << 16) |
					   (MCI_FIFOSIZE);
			box->row_offset = MCI_FIFOSIZE;

			box->num_rows = rows * ((1 << 16) + 1);
			box->cmd |= CMD_SRC_CRCI(crci);
		} else {
			box->src_row_addr = sg_dma_address(sg);
			box->dst_row_addr = msmsdcc_fifo_addr(host);

			box->src_dst_len = (MCI_FIFOSIZE << 16) |
					   (MCI_FIFOSIZE);
			box->row_offset = (MCI_FIFOSIZE << 16);

			box->num_rows = rows * ((1 << 16) + 1);
			box->cmd |= CMD_DST_CRCI(crci);
		}
		box++;
		sg++;
	}

	/* location of command block must be 64 bit aligned */
	BUG_ON(host->dma.cmd_busaddr & 0x07);

	nc->cmdptr = (host->dma.cmd_busaddr >> 3) | CMD_PTR_LP;
	host->dma.hdr.cmdptr = DMOV_CMD_PTR_LIST |
			       DMOV_CMD_ADDR(host->dma.cmdptr_busaddr);
	host->dma.hdr.complete_func = msmsdcc_dma_complete_func;

	return 0;
}