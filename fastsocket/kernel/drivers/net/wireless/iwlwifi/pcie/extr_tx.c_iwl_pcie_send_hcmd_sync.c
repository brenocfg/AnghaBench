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
struct iwl_queue {int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct iwl_txq {TYPE_2__* entries; struct iwl_queue q; } ;
struct iwl_trans_pcie {size_t cmd_queue; struct iwl_txq* txq; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; } ;
struct iwl_trans {int dummy; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/ * resp_pkt; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ meta; } ;

/* Variables and functions */
 int CMD_WANT_SKB ; 
 int EIO ; 
 int ERFKILL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOST_COMPLETE_TIMEOUT ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int /*<<< orphan*/ ,...) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_HCMD_ACTIVE ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cmd_string (struct iwl_trans_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_pcie_enqueue_hcmd (struct iwl_trans*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_pcie_send_hcmd_sync(struct iwl_trans *trans,
				   struct iwl_host_cmd *cmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int cmd_idx;
	int ret;

	IWL_DEBUG_INFO(trans, "Attempting to send sync command %s\n",
		       get_cmd_string(trans_pcie, cmd->id));

	if (WARN_ON(test_and_set_bit(STATUS_HCMD_ACTIVE,
				     &trans_pcie->status))) {
		IWL_ERR(trans, "Command %s: a command is already active!\n",
			get_cmd_string(trans_pcie, cmd->id));
		return -EIO;
	}

	IWL_DEBUG_INFO(trans, "Setting HCMD_ACTIVE for command %s\n",
		       get_cmd_string(trans_pcie, cmd->id));

	cmd_idx = iwl_pcie_enqueue_hcmd(trans, cmd);
	if (cmd_idx < 0) {
		ret = cmd_idx;
		clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
		IWL_ERR(trans,
			"Error sending %s: enqueue_hcmd failed: %d\n",
			get_cmd_string(trans_pcie, cmd->id), ret);
		return ret;
	}

	ret = wait_event_timeout(trans_pcie->wait_command_queue,
				 !test_bit(STATUS_HCMD_ACTIVE,
					   &trans_pcie->status),
				 HOST_COMPLETE_TIMEOUT);
	if (!ret) {
		if (test_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status)) {
			struct iwl_txq *txq =
				&trans_pcie->txq[trans_pcie->cmd_queue];
			struct iwl_queue *q = &txq->q;

			IWL_ERR(trans,
				"Error sending %s: time out after %dms.\n",
				get_cmd_string(trans_pcie, cmd->id),
				jiffies_to_msecs(HOST_COMPLETE_TIMEOUT));

			IWL_ERR(trans,
				"Current CMD queue read_ptr %d write_ptr %d\n",
				q->read_ptr, q->write_ptr);

			clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
			IWL_DEBUG_INFO(trans,
				       "Clearing HCMD_ACTIVE for command %s\n",
				       get_cmd_string(trans_pcie, cmd->id));
			ret = -ETIMEDOUT;
			goto cancel;
		}
	}

	if (test_bit(STATUS_FW_ERROR, &trans_pcie->status)) {
		IWL_ERR(trans, "FW error in SYNC CMD %s\n",
			get_cmd_string(trans_pcie, cmd->id));
		ret = -EIO;
		goto cancel;
	}

	if (test_bit(STATUS_RFKILL, &trans_pcie->status)) {
		IWL_DEBUG_RF_KILL(trans, "RFKILL in SYNC CMD... no rsp\n");
		ret = -ERFKILL;
		goto cancel;
	}

	if ((cmd->flags & CMD_WANT_SKB) && !cmd->resp_pkt) {
		IWL_ERR(trans, "Error: Response NULL in '%s'\n",
			get_cmd_string(trans_pcie, cmd->id));
		ret = -EIO;
		goto cancel;
	}

	return 0;

cancel:
	if (cmd->flags & CMD_WANT_SKB) {
		/*
		 * Cancel the CMD_WANT_SKB flag for the cmd in the
		 * TX cmd queue. Otherwise in case the cmd comes
		 * in later, it will possibly set an invalid
		 * address (cmd->meta.source).
		 */
		trans_pcie->txq[trans_pcie->cmd_queue].
			entries[cmd_idx].meta.flags &= ~CMD_WANT_SKB;
	}

	if (cmd->resp_pkt) {
		iwl_free_resp(cmd);
		cmd->resp_pkt = NULL;
	}

	return ret;
}