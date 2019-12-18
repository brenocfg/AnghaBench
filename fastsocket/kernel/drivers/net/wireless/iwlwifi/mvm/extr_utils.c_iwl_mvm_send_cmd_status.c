#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int flags; } ;
struct iwl_rx_packet {scalar_t__ data; int /*<<< orphan*/  len_n_flags; TYPE_1__ hdr; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  mutex; } ;
struct iwl_host_cmd {int flags; struct iwl_rx_packet* resp_pkt; } ;
struct iwl_cmd_response {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_SYNC ; 
 int CMD_WANT_SKB ; 
 int EINVAL ; 
 int EIO ; 
 int ERFKILL ; 
 int FH_RSCSR_FRAME_SIZE_MSK ; 
 int IWL_CMD_FAILED_MSK ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_trans_send_cmd (int /*<<< orphan*/ ,struct iwl_host_cmd*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_send_cmd_status(struct iwl_mvm *mvm, struct iwl_host_cmd *cmd,
			    u32 *status)
{
	struct iwl_rx_packet *pkt;
	struct iwl_cmd_response *resp;
	int ret, resp_len;

	lockdep_assert_held(&mvm->mutex);

	/*
	 * Only synchronous commands can wait for status,
	 * we use WANT_SKB so the caller can't.
	 */
	if (WARN_ONCE(cmd->flags & (CMD_ASYNC | CMD_WANT_SKB),
		      "cmd flags %x", cmd->flags))
		return -EINVAL;

	cmd->flags |= CMD_SYNC | CMD_WANT_SKB;

	ret = iwl_trans_send_cmd(mvm->trans, cmd);
	if (ret == -ERFKILL) {
		/*
		 * The command failed because of RFKILL, don't update
		 * the status, leave it as success and return 0.
		 */
		return 0;
	} else if (ret) {
		return ret;
	}

	pkt = cmd->resp_pkt;
	/* Can happen if RFKILL is asserted */
	if (!pkt) {
		ret = 0;
		goto out_free_resp;
	}

	if (pkt->hdr.flags & IWL_CMD_FAILED_MSK) {
		ret = -EIO;
		goto out_free_resp;
	}

	resp_len = le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_FRAME_SIZE_MSK;
	if (WARN_ON_ONCE(resp_len != sizeof(pkt->hdr) + sizeof(*resp))) {
		ret = -EIO;
		goto out_free_resp;
	}

	resp = (void *)pkt->data;
	*status = le32_to_cpu(resp->status);
 out_free_resp:
	iwl_free_resp(cmd);
	return ret;
}