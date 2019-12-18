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
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm_alive_data {int /*<<< orphan*/  scd_base_addr; int /*<<< orphan*/  valid; } ;
struct iwl_mvm {int cur_ucode; int ucode_loaded; int* queue_to_mac80211; scalar_t__ transport_queue_stop; int /*<<< orphan*/ * queue_stop_count; int /*<<< orphan*/  trans; int /*<<< orphan*/  notif_wait; } ;
struct fw_img {int dummy; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int IWL_INVALID_MAC80211_QUEUE ; 
 int IWL_MAX_HW_QUEUES ; 
 int IWL_MVM_CMD_QUEUE ; 
 int IWL_MVM_FIRST_AGG_QUEUE ; 
 int IWL_UCODE_INIT ; 
#define  MVM_ALIVE 128 
 int /*<<< orphan*/  MVM_UCODE_ALIVE_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_alive_fn ; 
 struct fw_img* iwl_get_ucode_image (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_alive_data*) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int /*<<< orphan*/  iwl_trans_fw_alive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_trans_start_fw (int /*<<< orphan*/ ,struct fw_img const*,int) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_load_ucode_wait_alive(struct iwl_mvm *mvm,
					 enum iwl_ucode_type ucode_type)
{
	struct iwl_notification_wait alive_wait;
	struct iwl_mvm_alive_data alive_data;
	const struct fw_img *fw;
	int ret, i;
	enum iwl_ucode_type old_type = mvm->cur_ucode;
	static const u8 alive_cmd[] = { MVM_ALIVE };

	mvm->cur_ucode = ucode_type;
	fw = iwl_get_ucode_image(mvm, ucode_type);

	mvm->ucode_loaded = false;

	if (!fw)
		return -EINVAL;

	iwl_init_notification_wait(&mvm->notif_wait, &alive_wait,
				   alive_cmd, ARRAY_SIZE(alive_cmd),
				   iwl_alive_fn, &alive_data);

	ret = iwl_trans_start_fw(mvm->trans, fw, ucode_type == IWL_UCODE_INIT);
	if (ret) {
		mvm->cur_ucode = old_type;
		iwl_remove_notification(&mvm->notif_wait, &alive_wait);
		return ret;
	}

	/*
	 * Some things may run in the background now, but we
	 * just wait for the ALIVE notification here.
	 */
	ret = iwl_wait_notification(&mvm->notif_wait, &alive_wait,
				    MVM_UCODE_ALIVE_TIMEOUT);
	if (ret) {
		mvm->cur_ucode = old_type;
		return ret;
	}

	if (!alive_data.valid) {
		IWL_ERR(mvm, "Loaded ucode is not valid!\n");
		mvm->cur_ucode = old_type;
		return -EIO;
	}

	iwl_trans_fw_alive(mvm->trans, alive_data.scd_base_addr);

	/*
	 * Note: all the queues are enabled as part of the interface
	 * initialization, but in firmware restart scenarios they
	 * could be stopped, so wake them up. In firmware restart,
	 * mac80211 will have the queues stopped as well until the
	 * reconfiguration completes. During normal startup, they
	 * will be empty.
	 */

	for (i = 0; i < IWL_MAX_HW_QUEUES; i++) {
		if (i < IWL_MVM_FIRST_AGG_QUEUE && i != IWL_MVM_CMD_QUEUE)
			mvm->queue_to_mac80211[i] = i;
		else
			mvm->queue_to_mac80211[i] = IWL_INVALID_MAC80211_QUEUE;
		atomic_set(&mvm->queue_stop_count[i], 0);
	}

	mvm->transport_queue_stop = 0;

	mvm->ucode_loaded = true;

	return 0;
}