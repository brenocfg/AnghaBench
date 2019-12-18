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
typedef  int u32 ;
struct ohci_iso_recv {int nblocks; int buf_stride; scalar_t__ dma_mode; int block_irq_interval; int /*<<< orphan*/  prog; struct dma_cmd* block; } ;
struct hpsb_iso {int /*<<< orphan*/  data_buf; struct ohci_iso_recv* hostdata; } ;
struct dma_cmd {int branchAddress; void* status; void* address; void* control; } ;

/* Variables and functions */
 scalar_t__ BUFFER_FILL_MODE ; 
 void* cpu_to_le32 (int) ; 
 int dma_prog_region_offset_to_bus (int /*<<< orphan*/ *,unsigned long) ; 
 int dma_region_offset_to_bus (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ohci_iso_recv_program(struct hpsb_iso *iso)
{
	struct ohci_iso_recv *recv = iso->hostdata;
	int blk;

	/* address of 'branch' field in previous DMA descriptor */
	u32 *prev_branch = NULL;

	for (blk = 0; blk < recv->nblocks; blk++) {
		u32 control;

		/* the DMA descriptor */
		struct dma_cmd *cmd = &recv->block[blk];

		/* offset of the DMA descriptor relative to the DMA prog buffer */
		unsigned long prog_offset = blk * sizeof(struct dma_cmd);

		/* offset of this packet's data within the DMA buffer */
		unsigned long buf_offset = blk * recv->buf_stride;

		if (recv->dma_mode == BUFFER_FILL_MODE) {
			control = 2 << 28; /* INPUT_MORE */
		} else {
			control = 3 << 28; /* INPUT_LAST */
		}

		control |= 8 << 24; /* s = 1, update xferStatus and resCount */

		/* interrupt on last block, and at intervals */
		if (blk == recv->nblocks-1 || (blk % recv->block_irq_interval) == 0) {
			control |= 3 << 20; /* want interrupt */
		}

		control |= 3 << 18; /* enable branch to address */
		control |= recv->buf_stride;

		cmd->control = cpu_to_le32(control);
		cmd->address = cpu_to_le32(dma_region_offset_to_bus(&iso->data_buf, buf_offset));
		cmd->branchAddress = 0; /* filled in on next loop */
		cmd->status = cpu_to_le32(recv->buf_stride);

		/* link the previous descriptor to this one */
		if (prev_branch) {
			*prev_branch = cpu_to_le32(dma_prog_region_offset_to_bus(&recv->prog, prog_offset) | 1);
		}

		prev_branch = &cmd->branchAddress;
	}

	/* the final descriptor's branch address and Z should be left at 0 */
}