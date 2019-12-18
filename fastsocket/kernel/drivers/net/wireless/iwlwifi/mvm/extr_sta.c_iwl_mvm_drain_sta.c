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
typedef  int u32 ;
struct iwl_mvm_sta {int /*<<< orphan*/  sta_id; int /*<<< orphan*/  mac_id_n_color; } ;
struct iwl_mvm_add_sta_cmd {void* station_flags_msk; void* station_flags; int /*<<< orphan*/  add_modify; int /*<<< orphan*/  sta_id; void* mac_id_n_color; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
#define  ADD_STA_SUCCESS 128 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STA_FLG_DRAIN_FLOW ; 
 int /*<<< orphan*/  STA_MODE_MODIFY ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int,struct iwl_mvm_add_sta_cmd*,int*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_drain_sta(struct iwl_mvm *mvm, struct iwl_mvm_sta *mvmsta,
		      bool drain)
{
	struct iwl_mvm_add_sta_cmd cmd = {};
	int ret;
	u32 status;

	lockdep_assert_held(&mvm->mutex);

	cmd.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color);
	cmd.sta_id = mvmsta->sta_id;
	cmd.add_modify = STA_MODE_MODIFY;
	cmd.station_flags = drain ? cpu_to_le32(STA_FLG_DRAIN_FLOW) : 0;
	cmd.station_flags_msk = cpu_to_le32(STA_FLG_DRAIN_FLOW);

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA, sizeof(cmd),
					  &cmd, &status);
	if (ret)
		return ret;

	switch (status) {
	case ADD_STA_SUCCESS:
		IWL_DEBUG_INFO(mvm, "Frames for staid %d will drained in fw\n",
			       mvmsta->sta_id);
		break;
	default:
		ret = -EIO;
		IWL_ERR(mvm, "Couldn't drain frames for staid %d\n",
			mvmsta->sta_id);
		break;
	}

	return ret;
}