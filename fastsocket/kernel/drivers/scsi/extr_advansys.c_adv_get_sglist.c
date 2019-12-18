#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct scatterlist {int dummy; } ;
struct asc_board {TYPE_3__* adv_sgblkp; } ;
struct TYPE_11__ {struct TYPE_11__* next_sgblkp; int /*<<< orphan*/  sg_block; } ;
typedef  TYPE_3__ adv_sgblk_t ;
struct TYPE_12__ {TYPE_3__* sgblkp; int /*<<< orphan*/  scsi_req_q; } ;
typedef  TYPE_4__ adv_req_t ;
struct TYPE_14__ {void* sg_real_addr; TYPE_5__* sg_list_ptr; } ;
struct TYPE_13__ {long sg_ptr; int sg_cnt; TYPE_1__* sg_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  host; } ;
struct TYPE_9__ {void* sg_count; void* sg_addr; } ;
typedef  TYPE_5__ ADV_SG_BLOCK ;
typedef  TYPE_6__ ADV_SCSI_REQ_Q ;
typedef  int /*<<< orphan*/  ADV_PADDR ;

/* Variables and functions */
 scalar_t__ ADV_32BALIGN (int /*<<< orphan*/ *) ; 
 scalar_t__ ADV_8BALIGN (int /*<<< orphan*/ *) ; 
 int ADV_SUCCESS ; 
 int ASC_BUSY ; 
 int /*<<< orphan*/  ASC_DBG (int,char*) ; 
 int /*<<< orphan*/  ASC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASC_STATS_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int NO_OF_SG_PER_BLOCK ; 
 int /*<<< orphan*/  adv_build_nosg ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  virt_to_bus (TYPE_5__*) ; 
 int /*<<< orphan*/  xfer_sect ; 

__attribute__((used)) static int
adv_get_sglist(struct asc_board *boardp, adv_req_t *reqp, struct scsi_cmnd *scp,
	       int use_sg)
{
	adv_sgblk_t *sgblkp;
	ADV_SCSI_REQ_Q *scsiqp;
	struct scatterlist *slp;
	int sg_elem_cnt;
	ADV_SG_BLOCK *sg_block, *prev_sg_block;
	ADV_PADDR sg_block_paddr;
	int i;

	scsiqp = (ADV_SCSI_REQ_Q *)ADV_32BALIGN(&reqp->scsi_req_q);
	slp = scsi_sglist(scp);
	sg_elem_cnt = use_sg;
	prev_sg_block = NULL;
	reqp->sgblkp = NULL;

	for (;;) {
		/*
		 * Allocate a 'adv_sgblk_t' structure from the board free
		 * list. One 'adv_sgblk_t' structure holds NO_OF_SG_PER_BLOCK
		 * (15) scatter-gather elements.
		 */
		if ((sgblkp = boardp->adv_sgblkp) == NULL) {
			ASC_DBG(1, "no free adv_sgblk_t\n");
			ASC_STATS(scp->device->host, adv_build_nosg);

			/*
			 * Allocation failed. Free 'adv_sgblk_t' structures
			 * already allocated for the request.
			 */
			while ((sgblkp = reqp->sgblkp) != NULL) {
				/* Remove 'sgblkp' from the request list. */
				reqp->sgblkp = sgblkp->next_sgblkp;

				/* Add 'sgblkp' to the board free list. */
				sgblkp->next_sgblkp = boardp->adv_sgblkp;
				boardp->adv_sgblkp = sgblkp;
			}
			return ASC_BUSY;
		}

		/* Complete 'adv_sgblk_t' board allocation. */
		boardp->adv_sgblkp = sgblkp->next_sgblkp;
		sgblkp->next_sgblkp = NULL;

		/*
		 * Get 8 byte aligned virtual and physical addresses
		 * for the allocated ADV_SG_BLOCK structure.
		 */
		sg_block = (ADV_SG_BLOCK *)ADV_8BALIGN(&sgblkp->sg_block);
		sg_block_paddr = virt_to_bus(sg_block);

		/*
		 * Check if this is the first 'adv_sgblk_t' for the
		 * request.
		 */
		if (reqp->sgblkp == NULL) {
			/* Request's first scatter-gather block. */
			reqp->sgblkp = sgblkp;

			/*
			 * Set ADV_SCSI_REQ_T ADV_SG_BLOCK virtual and physical
			 * address pointers.
			 */
			scsiqp->sg_list_ptr = sg_block;
			scsiqp->sg_real_addr = cpu_to_le32(sg_block_paddr);
		} else {
			/* Request's second or later scatter-gather block. */
			sgblkp->next_sgblkp = reqp->sgblkp;
			reqp->sgblkp = sgblkp;

			/*
			 * Point the previous ADV_SG_BLOCK structure to
			 * the newly allocated ADV_SG_BLOCK structure.
			 */
			prev_sg_block->sg_ptr = cpu_to_le32(sg_block_paddr);
		}

		for (i = 0; i < NO_OF_SG_PER_BLOCK; i++) {
			sg_block->sg_list[i].sg_addr =
					cpu_to_le32(sg_dma_address(slp));
			sg_block->sg_list[i].sg_count =
					cpu_to_le32(sg_dma_len(slp));
			ASC_STATS_ADD(scp->device->host, xfer_sect,
				      DIV_ROUND_UP(sg_dma_len(slp), 512));

			if (--sg_elem_cnt == 0) {	/* Last ADV_SG_BLOCK and scatter-gather entry. */
				sg_block->sg_cnt = i + 1;
				sg_block->sg_ptr = 0L;	/* Last ADV_SG_BLOCK in list. */
				return ADV_SUCCESS;
			}
			slp++;
		}
		sg_block->sg_cnt = NO_OF_SG_PER_BLOCK;
		prev_sg_block = sg_block;
	}
}