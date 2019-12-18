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
typedef  void* u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_sta {int /*<<< orphan*/  sta_id; int /*<<< orphan*/  mac_id_n_color; } ;
struct iwl_mvm_add_sta_cmd {int /*<<< orphan*/  modify_mask; void* remove_immediate_ba_tid; int /*<<< orphan*/  add_immediate_ba_ssn; void* add_immediate_ba_tid; int /*<<< orphan*/  add_modify; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  mac_id_n_color; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
#define  ADD_STA_IMMEDIATE_BA_FAILURE 129 
#define  ADD_STA_SUCCESS 128 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,char*,int) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  STA_MODE_MODIFY ; 
 int /*<<< orphan*/  STA_MODIFY_ADD_BA_TID ; 
 int /*<<< orphan*/  STA_MODIFY_REMOVE_BA_TID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int,struct iwl_mvm_add_sta_cmd*,int*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_sta_rx_agg(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
		       int tid, u16 ssn, bool start)
{
	struct iwl_mvm_sta *mvm_sta = (void *)sta->drv_priv;
	struct iwl_mvm_add_sta_cmd cmd = {};
	int ret;
	u32 status;

	lockdep_assert_held(&mvm->mutex);

	cmd.mac_id_n_color = cpu_to_le32(mvm_sta->mac_id_n_color);
	cmd.sta_id = mvm_sta->sta_id;
	cmd.add_modify = STA_MODE_MODIFY;
	if (start) {
		cmd.add_immediate_ba_tid = (u8) tid;
		cmd.add_immediate_ba_ssn = cpu_to_le16(ssn);
	} else {
		cmd.remove_immediate_ba_tid = (u8) tid;
	}
	cmd.modify_mask = start ? STA_MODIFY_ADD_BA_TID :
				  STA_MODIFY_REMOVE_BA_TID;

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA, sizeof(cmd),
					  &cmd, &status);
	if (ret)
		return ret;

	switch (status) {
	case ADD_STA_SUCCESS:
		IWL_DEBUG_INFO(mvm, "RX BA Session %sed in fw\n",
			       start ? "start" : "stopp");
		break;
	case ADD_STA_IMMEDIATE_BA_FAILURE:
		IWL_WARN(mvm, "RX BA Session refused by fw\n");
		ret = -ENOSPC;
		break;
	default:
		ret = -EIO;
		IWL_ERR(mvm, "RX BA Session failed %sing, status 0x%x\n",
			start ? "start" : "stopp", status);
		break;
	}

	return ret;
}