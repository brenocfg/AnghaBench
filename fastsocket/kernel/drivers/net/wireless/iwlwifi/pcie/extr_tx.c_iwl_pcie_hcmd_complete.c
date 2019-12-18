#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct page {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct iwl_txq {int /*<<< orphan*/  lock; int /*<<< orphan*/ * tfds; TYPE_2__* entries; TYPE_5__ q; } ;
struct iwl_trans_pcie {size_t cmd_queue; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; int /*<<< orphan*/  rx_page_order; struct iwl_txq* txq; } ;
struct iwl_trans {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sequence; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
struct iwl_device_cmd {TYPE_4__ hdr; } ;
struct iwl_cmd_meta {int flags; TYPE_3__* source; } ;
struct TYPE_8__ {unsigned long _rx_page_addr; int handler_status; int /*<<< orphan*/  _rx_page_order; struct iwl_rx_packet* resp_pkt; } ;
struct TYPE_7__ {struct iwl_cmd_meta meta; struct iwl_device_cmd* cmd; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_WANT_SKB ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int SEQ_TO_INDEX (int /*<<< orphan*/ ) ; 
 int SEQ_TO_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_HCMD_ACTIVE ; 
 scalar_t__ WARN (int,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_cmd_index (TYPE_5__*,int) ; 
 int /*<<< orphan*/  get_cmd_string (struct iwl_trans_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_cmdq_reclaim (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_unmap (struct iwl_trans*,struct iwl_cmd_meta*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_print_hex_error (struct iwl_trans*,struct iwl_rx_packet*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 struct page* rxb_steal_page (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iwl_pcie_hcmd_complete(struct iwl_trans *trans,
			    struct iwl_rx_cmd_buffer *rxb, int handler_status)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	int txq_id = SEQ_TO_QUEUE(sequence);
	int index = SEQ_TO_INDEX(sequence);
	int cmd_index;
	struct iwl_device_cmd *cmd;
	struct iwl_cmd_meta *meta;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq = &trans_pcie->txq[trans_pcie->cmd_queue];

	/* If a Tx command is being handled and it isn't in the actual
	 * command queue then there a command routing bug has been introduced
	 * in the queue management code. */
	if (WARN(txq_id != trans_pcie->cmd_queue,
		 "wrong command queue %d (should be %d), sequence 0x%X readp=%d writep=%d\n",
		 txq_id, trans_pcie->cmd_queue, sequence,
		 trans_pcie->txq[trans_pcie->cmd_queue].q.read_ptr,
		 trans_pcie->txq[trans_pcie->cmd_queue].q.write_ptr)) {
		iwl_print_hex_error(trans, pkt, 32);
		return;
	}

	spin_lock_bh(&txq->lock);

	cmd_index = get_cmd_index(&txq->q, index);
	cmd = txq->entries[cmd_index].cmd;
	meta = &txq->entries[cmd_index].meta;

	iwl_pcie_tfd_unmap(trans, meta, &txq->tfds[index]);

	/* Input error checking is done when commands are added to queue. */
	if (meta->flags & CMD_WANT_SKB) {
		struct page *p = rxb_steal_page(rxb);

		meta->source->resp_pkt = pkt;
		meta->source->_rx_page_addr = (unsigned long)page_address(p);
		meta->source->_rx_page_order = trans_pcie->rx_page_order;
		meta->source->handler_status = handler_status;
	}

	iwl_pcie_cmdq_reclaim(trans, txq_id, index);

	if (!(meta->flags & CMD_ASYNC)) {
		if (!test_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status)) {
			IWL_WARN(trans,
				 "HCMD_ACTIVE already clear for command %s\n",
				 get_cmd_string(trans_pcie, cmd->hdr.cmd));
		}
		clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       get_cmd_string(trans_pcie, cmd->hdr.cmd));
		wake_up(&trans_pcie->wait_command_queue);
	}

	meta->flags = 0;

	spin_unlock_bh(&txq->lock);
}