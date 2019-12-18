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
typedef  int u8 ;
struct iwlagn_scd_bc_tbl {void** tfd_offset; } ;
struct TYPE_8__ {int id; int read_ptr; } ;
struct iwl_txq {TYPE_4__ q; TYPE_3__* entries; } ;
struct iwl_tx_cmd {int sta_id; } ;
struct TYPE_5__ {struct iwlagn_scd_bc_tbl* addr; } ;
struct iwl_trans_pcie {int cmd_queue; TYPE_1__ scd_bc_tbls; } ;
struct iwl_trans {int dummy; } ;
typedef  void* __le16 ;
struct TYPE_7__ {TYPE_2__* cmd; } ;
struct TYPE_6__ {scalar_t__ payload; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int TFD_QUEUE_SIZE_BC_DUP ; 
 int TFD_QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void iwl_pcie_txq_inval_byte_cnt_tbl(struct iwl_trans *trans,
					    struct iwl_txq *txq)
{
	struct iwl_trans_pcie *trans_pcie =
		IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwlagn_scd_bc_tbl *scd_bc_tbl = trans_pcie->scd_bc_tbls.addr;
	int txq_id = txq->q.id;
	int read_ptr = txq->q.read_ptr;
	u8 sta_id = 0;
	__le16 bc_ent;
	struct iwl_tx_cmd *tx_cmd =
		(void *)txq->entries[txq->q.read_ptr].cmd->payload;

	WARN_ON(read_ptr >= TFD_QUEUE_SIZE_MAX);

	if (txq_id != trans_pcie->cmd_queue)
		sta_id = tx_cmd->sta_id;

	bc_ent = cpu_to_le16(1 | (sta_id << 12));
	scd_bc_tbl[txq_id].tfd_offset[read_ptr] = bc_ent;

	if (read_ptr < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbl[txq_id].
			tfd_offset[TFD_QUEUE_SIZE_MAX + read_ptr] = bc_ent;
}