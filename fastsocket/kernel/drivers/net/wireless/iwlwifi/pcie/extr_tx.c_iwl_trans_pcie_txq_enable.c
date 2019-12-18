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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct iwl_trans_pcie {int cmd_queue; TYPE_2__* txq; scalar_t__ scd_base_addr; int /*<<< orphan*/  queue_used; } ;
struct iwl_trans {int dummy; } ;
struct TYPE_3__ {int read_ptr; int write_ptr; } ;
struct TYPE_4__ {int active; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int BUILD_RAxTID (int,int) ; 
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int,int,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  SCD_AGGR_SEL ; 
 scalar_t__ SCD_CONTEXT_QUEUE_OFFSET (int) ; 
 int /*<<< orphan*/  SCD_QUEUECHAIN_SEL ; 
 int SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK ; 
 int SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS ; 
 int SCD_QUEUE_CTX_REG2_WIN_SIZE_MSK ; 
 int SCD_QUEUE_CTX_REG2_WIN_SIZE_POS ; 
 int /*<<< orphan*/  SCD_QUEUE_RDPTR (int) ; 
 int /*<<< orphan*/  SCD_QUEUE_STATUS_BITS (int) ; 
 int SCD_QUEUE_STTS_REG_MSK ; 
 int SCD_QUEUE_STTS_REG_POS_ACTIVE ; 
 int SCD_QUEUE_STTS_REG_POS_TXF ; 
 int SCD_QUEUE_STTS_REG_POS_WSL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_txq_set_inactive (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_pcie_txq_set_ratid_map (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_write_mem32 (struct iwl_trans*,scalar_t__,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

void iwl_trans_pcie_txq_enable(struct iwl_trans *trans, int txq_id, int fifo,
			       int sta_id, int tid, int frame_limit, u16 ssn)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	if (test_and_set_bit(txq_id, trans_pcie->queue_used))
		WARN_ONCE(1, "queue %d already used - expect issues", txq_id);

	/* Stop this Tx queue before configuring it */
	iwl_pcie_txq_set_inactive(trans, txq_id);

	/* Set this queue as a chain-building queue unless it is CMD queue */
	if (txq_id != trans_pcie->cmd_queue)
		iwl_set_bits_prph(trans, SCD_QUEUECHAIN_SEL, BIT(txq_id));

	/* If this queue is mapped to a certain station: it is an AGG queue */
	if (sta_id >= 0) {
		u16 ra_tid = BUILD_RAxTID(sta_id, tid);

		/* Map receiver-address / traffic-ID to this queue */
		iwl_pcie_txq_set_ratid_map(trans, ra_tid, txq_id);

		/* enable aggregations for the queue */
		iwl_set_bits_prph(trans, SCD_AGGR_SEL, BIT(txq_id));
	} else {
		/*
		 * disable aggregations for the queue, this will also make the
		 * ra_tid mapping configuration irrelevant since it is now a
		 * non-AGG queue.
		 */
		iwl_clear_bits_prph(trans, SCD_AGGR_SEL, BIT(txq_id));
	}

	/* Place first TFD at index corresponding to start sequence number.
	 * Assumes that ssn_idx is valid (!= 0xFFF) */
	trans_pcie->txq[txq_id].q.read_ptr = (ssn & 0xff);
	trans_pcie->txq[txq_id].q.write_ptr = (ssn & 0xff);

	iwl_write_direct32(trans, HBUS_TARG_WRPTR,
			   (ssn & 0xff) | (txq_id << 8));
	iwl_write_prph(trans, SCD_QUEUE_RDPTR(txq_id), ssn);

	/* Set up Tx window size and frame limit for this queue */
	iwl_trans_write_mem32(trans, trans_pcie->scd_base_addr +
			SCD_CONTEXT_QUEUE_OFFSET(txq_id), 0);
	iwl_trans_write_mem32(trans, trans_pcie->scd_base_addr +
			SCD_CONTEXT_QUEUE_OFFSET(txq_id) + sizeof(u32),
			((frame_limit << SCD_QUEUE_CTX_REG2_WIN_SIZE_POS) &
				SCD_QUEUE_CTX_REG2_WIN_SIZE_MSK) |
			((frame_limit << SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS) &
				SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK));

	/* Set up Status area in SRAM, map to Tx DMA/FIFO, activate the queue */
	iwl_write_prph(trans, SCD_QUEUE_STATUS_BITS(txq_id),
		       (1 << SCD_QUEUE_STTS_REG_POS_ACTIVE) |
		       (fifo << SCD_QUEUE_STTS_REG_POS_TXF) |
		       (1 << SCD_QUEUE_STTS_REG_POS_WSL) |
		       SCD_QUEUE_STTS_REG_MSK);
	trans_pcie->txq[txq_id].active = true;
	IWL_DEBUG_TX_QUEUES(trans, "Activate queue %d on FIFO %d WrPtr: %d\n",
			    txq_id, fifo, ssn & 0xff);
}