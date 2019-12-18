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
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/  phy_db; int /*<<< orphan*/  fw; int /*<<< orphan*/  init_ucode_run; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ init_dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int iwl_mvm_add_aux_sta (struct iwl_mvm*) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_run_init_mvm_ucode (struct iwl_mvm*,int) ; 
 int iwl_send_bt_init_conf (struct iwl_mvm*) ; 
 int iwl_send_bt_prio_tbl (struct iwl_mvm*) ; 
 int iwl_send_phy_cfg_cmd (struct iwl_mvm*) ; 
 int iwl_send_phy_db_data (int /*<<< orphan*/ ) ; 
 int iwl_send_tx_ant_cfg (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_trans_start_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 TYPE_1__ iwlmvm_mod_params ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_up(struct iwl_mvm *mvm)
{
	int ret, i;

	lockdep_assert_held(&mvm->mutex);

	ret = iwl_trans_start_hw(mvm->trans);
	if (ret)
		return ret;

	/* If we were in RFKILL during module loading, load init ucode now */
	if (!mvm->init_ucode_run) {
		ret = iwl_run_init_mvm_ucode(mvm, false);
		if (ret && !iwlmvm_mod_params.init_dbg) {
			IWL_ERR(mvm, "Failed to run INIT ucode: %d\n", ret);
			goto error;
		}
	}

	if (iwlmvm_mod_params.init_dbg)
		return 0;

	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_REGULAR);
	if (ret) {
		IWL_ERR(mvm, "Failed to start RT ucode: %d\n", ret);
		goto error;
	}

	ret = iwl_send_tx_ant_cfg(mvm, iwl_fw_valid_tx_ant(mvm->fw));
	if (ret)
		goto error;

	ret = iwl_send_bt_prio_tbl(mvm);
	if (ret)
		goto error;

	ret = iwl_send_bt_init_conf(mvm);
	if (ret)
		goto error;

	/* Send phy db control command and then phy db calibration*/
	ret = iwl_send_phy_db_data(mvm->phy_db);
	if (ret)
		goto error;

	ret = iwl_send_phy_cfg_cmd(mvm);
	if (ret)
		goto error;

	/* init the fw <-> mac80211 STA mapping */
	for (i = 0; i < IWL_MVM_STATION_COUNT; i++)
		RCU_INIT_POINTER(mvm->fw_id_to_mac_id[i], NULL);

	/* Add auxiliary station for scanning */
	ret = iwl_mvm_add_aux_sta(mvm);
	if (ret)
		goto error;

	IWL_DEBUG_INFO(mvm, "RT uCode started.\n");

	return 0;
 error:
	iwl_trans_stop_device(mvm->trans);
	return ret;
}