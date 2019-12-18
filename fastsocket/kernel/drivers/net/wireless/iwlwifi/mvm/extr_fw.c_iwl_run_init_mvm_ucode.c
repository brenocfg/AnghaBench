#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_nvm_data {int dummy; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm {int init_ucode_run; TYPE_3__* nvm_data; int /*<<< orphan*/  trans; int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  fw; int /*<<< orphan*/  phy_db; int /*<<< orphan*/  mutex; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  init_dbg; } ;
struct TYPE_8__ {int valid_rx_ant; int valid_tx_ant; TYPE_2__* bands; scalar_t__ channels; } ;
struct TYPE_7__ {int n_channels; int n_bitrates; TYPE_1__* bitrates; scalar_t__ channels; } ;
struct TYPE_6__ {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CALIB_RES_NOTIF_PHY_DB 129 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  INIT_COMPLETE_NOTIF 128 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_INIT ; 
 int /*<<< orphan*/  MVM_UCODE_CALIB_TIMEOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_nvm_check_version (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int iwl_nvm_init (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_send_bt_prio_tbl (struct iwl_mvm*) ; 
 int iwl_send_phy_cfg_cmd (struct iwl_mvm*) ; 
 int iwl_send_tx_ant_cfg (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_set_default_calibrations (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_wait_phy_db_entry ; 
 TYPE_4__ iwlmvm_mod_params ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_run_init_mvm_ucode(struct iwl_mvm *mvm, bool read_nvm)
{
	struct iwl_notification_wait calib_wait;
	static const u8 init_complete[] = {
		INIT_COMPLETE_NOTIF,
		CALIB_RES_NOTIF_PHY_DB
	};
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (mvm->init_ucode_run)
		return 0;

	iwl_init_notification_wait(&mvm->notif_wait,
				   &calib_wait,
				   init_complete,
				   ARRAY_SIZE(init_complete),
				   iwl_wait_phy_db_entry,
				   mvm->phy_db);

	/* Will also start the device */
	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_INIT);
	if (ret) {
		IWL_ERR(mvm, "Failed to start INIT ucode: %d\n", ret);
		goto error;
	}

	ret = iwl_send_bt_prio_tbl(mvm);
	if (ret)
		goto error;

	if (read_nvm) {
		/* Read nvm */
		ret = iwl_nvm_init(mvm);
		if (ret) {
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			goto error;
		}
	}

	ret = iwl_nvm_check_version(mvm->nvm_data, mvm->trans);
	WARN_ON(ret);

	/* Send TX valid antennas before triggering calibrations */
	ret = iwl_send_tx_ant_cfg(mvm, iwl_fw_valid_tx_ant(mvm->fw));
	if (ret)
		goto error;

	/* need to set default values */
	ret = iwl_set_default_calibrations(mvm);
	if (ret)
		goto error;

	/*
	 * Send phy configurations command to init uCode
	 * to start the 16.0 uCode init image internal calibrations.
	 */
	ret = iwl_send_phy_cfg_cmd(mvm);
	if (ret) {
		IWL_ERR(mvm, "Failed to run INIT calibrations: %d\n",
			ret);
		goto error;
	}

	/*
	 * Some things may run in the background now, but we
	 * just wait for the calibration complete notification.
	 */
	ret = iwl_wait_notification(&mvm->notif_wait, &calib_wait,
			MVM_UCODE_CALIB_TIMEOUT);
	if (!ret)
		mvm->init_ucode_run = true;
	goto out;

error:
	iwl_remove_notification(&mvm->notif_wait, &calib_wait);
out:
	if (!iwlmvm_mod_params.init_dbg) {
		iwl_trans_stop_device(mvm->trans);
	} else if (!mvm->nvm_data) {
		/* we want to debug INIT and we have no NVM - fake */
		mvm->nvm_data = kzalloc(sizeof(struct iwl_nvm_data) +
					sizeof(struct ieee80211_channel) +
					sizeof(struct ieee80211_rate),
					GFP_KERNEL);
		if (!mvm->nvm_data)
			return -ENOMEM;
		mvm->nvm_data->valid_rx_ant = 1;
		mvm->nvm_data->valid_tx_ant = 1;
		mvm->nvm_data->bands[0].channels = mvm->nvm_data->channels;
		mvm->nvm_data->bands[0].n_channels = 1;
		mvm->nvm_data->bands[0].n_bitrates = 1;
		mvm->nvm_data->bands[0].bitrates =
			(void *)mvm->nvm_data->channels + 1;
		mvm->nvm_data->bands[0].bitrates->hw_value = 10;
	}

	return ret;
}