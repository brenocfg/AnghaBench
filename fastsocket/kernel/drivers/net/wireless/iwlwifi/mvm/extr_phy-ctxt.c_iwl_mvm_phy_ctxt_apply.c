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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_phy_context_cmd {int dummy; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  PHY_CONTEXT_CMD ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_cmd_data (struct iwl_mvm*,struct iwl_phy_context_cmd*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_cmd_hdr (struct iwl_mvm_phy_ctxt*,struct iwl_phy_context_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_phy_context_cmd*) ; 

__attribute__((used)) static int iwl_mvm_phy_ctxt_apply(struct iwl_mvm *mvm,
				  struct iwl_mvm_phy_ctxt *ctxt,
				  struct cfg80211_chan_def *chandef,
				  u8 chains_static, u8 chains_dynamic,
				  u32 action, u32 apply_time)
{
	struct iwl_phy_context_cmd cmd;
	int ret;

	/* Set the command header fields */
	iwl_mvm_phy_ctxt_cmd_hdr(ctxt, &cmd, action, apply_time);

	/* Set the command data */
	iwl_mvm_phy_ctxt_cmd_data(mvm, &cmd, chandef,
				  chains_static, chains_dynamic);

	ret = iwl_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD, CMD_SYNC,
				   sizeof(struct iwl_phy_context_cmd),
				   &cmd);
	if (ret)
		IWL_ERR(mvm, "PHY ctxt cmd error. ret=%d\n", ret);
	return ret;
}