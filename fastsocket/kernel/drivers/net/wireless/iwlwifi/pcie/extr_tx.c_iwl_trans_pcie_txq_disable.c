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
typedef  scalar_t__ u32 ;
struct iwl_trans_pcie {int /*<<< orphan*/  queue_used; scalar_t__ scd_base_addr; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__ const*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ SCD_TX_STTS_QUEUE_OFFSET (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  iwl_pcie_txq_set_inactive (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_pcie_txq_unmap (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_write_mem (struct iwl_trans*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

void iwl_trans_pcie_txq_disable(struct iwl_trans *trans, int txq_id)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 stts_addr = trans_pcie->scd_base_addr +
			SCD_TX_STTS_QUEUE_OFFSET(txq_id);
	static const u32 zero_val[4] = {};

	if (!test_and_clear_bit(txq_id, trans_pcie->queue_used)) {
		WARN_ONCE(1, "queue %d not used", txq_id);
		return;
	}

	iwl_pcie_txq_set_inactive(trans, txq_id);

	iwl_trans_write_mem(trans, stts_addr, (void *)zero_val,
			    ARRAY_SIZE(zero_val));

	iwl_pcie_txq_unmap(trans, txq_id);

	IWL_DEBUG_TX_QUEUES(trans, "Deactivate queue %d\n", txq_id);
}