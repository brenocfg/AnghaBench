#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sbp2_lu {int /*<<< orphan*/  protocol_work; int /*<<< orphan*/  shost; int /*<<< orphan*/  ne; int /*<<< orphan*/  cmd_orb_lock; scalar_t__ last_orb_dma; struct sbp2_command_orb* last_orb; int /*<<< orphan*/  command_block_agent_addr; struct sbp2_fwhost_info* hi; } ;
struct sbp2_fwhost_info {TYPE_2__* host; } ;
struct sbp2_command_orb {scalar_t__ next_ORB_hi; int /*<<< orphan*/  next_ORB_lo; } ;
struct sbp2_command_info {scalar_t__ command_orb_dma; struct sbp2_command_orb command_orb; } ;
typedef  scalar_t__ quadlet_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ device; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ ORB_SET_NODE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SBP2_DOORBELL_OFFSET ; 
 scalar_t__ SBP2_ORB_POINTER_OFFSET ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp2util_cpu_to_be32_buffer (scalar_t__*,int) ; 
 scalar_t__ sbp2util_node_write_no_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  sbp2util_write_doorbell ; 
 int /*<<< orphan*/  sbp2util_write_orb_pointer ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sbp2_link_orb_command(struct sbp2_lu *lu,
				  struct sbp2_command_info *cmd)
{
	struct sbp2_fwhost_info *hi = lu->hi;
	struct sbp2_command_orb *last_orb;
	dma_addr_t last_orb_dma;
	u64 addr = lu->command_block_agent_addr;
	quadlet_t data[2];
	size_t length;
	unsigned long flags;

	/* check to see if there are any previous orbs to use */
	spin_lock_irqsave(&lu->cmd_orb_lock, flags);
	last_orb = lu->last_orb;
	last_orb_dma = lu->last_orb_dma;
	if (!last_orb) {
		/*
		 * last_orb == NULL means: We know that the target's fetch agent
		 * is not active right now.
		 */
		addr += SBP2_ORB_POINTER_OFFSET;
		data[0] = ORB_SET_NODE_ID(hi->host->node_id);
		data[1] = cmd->command_orb_dma;
		sbp2util_cpu_to_be32_buffer(data, 8);
		length = 8;
	} else {
		/*
		 * last_orb != NULL means: We know that the target's fetch agent
		 * is (very probably) not dead or in reset state right now.
		 * We have an ORB already sent that we can append a new one to.
		 * The target's fetch agent may or may not have read this
		 * previous ORB yet.
		 */
		dma_sync_single_for_cpu(hi->host->device.parent, last_orb_dma,
					sizeof(struct sbp2_command_orb),
					DMA_TO_DEVICE);
		last_orb->next_ORB_lo = cpu_to_be32(cmd->command_orb_dma);
		wmb();
		/* Tells hardware that this pointer is valid */
		last_orb->next_ORB_hi = 0;
		dma_sync_single_for_device(hi->host->device.parent,
					   last_orb_dma,
					   sizeof(struct sbp2_command_orb),
					   DMA_TO_DEVICE);
		addr += SBP2_DOORBELL_OFFSET;
		data[0] = 0;
		length = 4;
	}
	lu->last_orb = &cmd->command_orb;
	lu->last_orb_dma = cmd->command_orb_dma;
	spin_unlock_irqrestore(&lu->cmd_orb_lock, flags);

	if (sbp2util_node_write_no_wait(lu->ne, addr, data, length)) {
		/*
		 * sbp2util_node_write_no_wait failed. We certainly ran out
		 * of transaction labels, perhaps just because there were no
		 * context switches which gave khpsbpkt a chance to collect
		 * free tlabels. Try again in non-atomic context. If necessary,
		 * the workqueue job will sleep to guaranteedly get a tlabel.
		 * We do not accept new commands until the job is over.
		 */
		scsi_block_requests(lu->shost);
		PREPARE_WORK(&lu->protocol_work,
			     last_orb ? sbp2util_write_doorbell:
					sbp2util_write_orb_pointer);
		schedule_work(&lu->protocol_work);
	}
}