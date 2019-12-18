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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_sta {struct ieee80211_vif* vif; } ;
struct iwl_mvm {int /*<<< orphan*/  fw_key_table; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  iv32; } ;
struct ieee80211_key_seq {TYPE_1__ tkip; } ;
struct ieee80211_key_conf {int cipher; scalar_t__ hw_key_idx; int /*<<< orphan*/  keyidx; int /*<<< orphan*/  keylen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_WEP (struct iwl_mvm*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 size_t IWL_MVM_STATION_COUNT ; 
 scalar_t__ STA_KEY_IDX_INVALID ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WLAN_CIPHER_SUITE_AES_CMAC ; 
#define  WLAN_CIPHER_SUITE_CCMP 129 
#define  WLAN_CIPHER_SUITE_TKIP 128 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_key_rx_seq (struct ieee80211_key_conf*,int /*<<< orphan*/ ,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  ieee80211_get_tkip_rx_p1k (struct ieee80211_key_conf*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t iwl_mvm_get_key_sta_id (struct ieee80211_vif*,struct ieee80211_sta*) ; 
 size_t* iwl_mvm_get_mac_addr (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int iwl_mvm_send_sta_igtk (struct iwl_mvm*,struct ieee80211_key_conf*,size_t,int) ; 
 int iwl_mvm_send_sta_key (struct iwl_mvm*,struct iwl_mvm_sta*,struct ieee80211_key_conf*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_set_fw_key_idx (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iwl_mvm_set_sta_key(struct iwl_mvm *mvm,
			struct ieee80211_vif *vif,
			struct ieee80211_sta *sta,
			struct ieee80211_key_conf *keyconf,
			bool have_key_offset)
{
	struct iwl_mvm_sta *mvm_sta;
	int ret;
	u8 *addr, sta_id;
	struct ieee80211_key_seq seq;
	u16 p1k[5];

	lockdep_assert_held(&mvm->mutex);

	/* Get the station id from the mvm local station table */
	sta_id = iwl_mvm_get_key_sta_id(vif, sta);
	if (sta_id == IWL_MVM_STATION_COUNT) {
		IWL_ERR(mvm, "Failed to find station id\n");
		return -EINVAL;
	}

	if (keyconf->cipher == WLAN_CIPHER_SUITE_AES_CMAC) {
		ret = iwl_mvm_send_sta_igtk(mvm, keyconf, sta_id, false);
		goto end;
	}

	/*
	 * It is possible that the 'sta' parameter is NULL, and thus
	 * there is a need to retrieve  the sta from the local station table.
	 */
	if (!sta) {
		sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[sta_id],
						lockdep_is_held(&mvm->mutex));
		if (IS_ERR_OR_NULL(sta)) {
			IWL_ERR(mvm, "Invalid station id\n");
			return -EINVAL;
		}
	}

	mvm_sta = (struct iwl_mvm_sta *)sta->drv_priv;
	if (WARN_ON_ONCE(mvm_sta->vif != vif))
		return -EINVAL;

	if (!have_key_offset) {
		/*
		 * The D3 firmware hardcodes the PTK offset to 0, so we have to
		 * configure it there. As a result, this workaround exists to
		 * let the caller set the key offset (hw_key_idx), see d3.c.
		 */
		keyconf->hw_key_idx = iwl_mvm_set_fw_key_idx(mvm);
		if (keyconf->hw_key_idx == STA_KEY_IDX_INVALID)
			return -ENOSPC;
	}

	switch (keyconf->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
		addr = iwl_mvm_get_mac_addr(mvm, vif, sta);
		/* get phase 1 key from mac80211 */
		ieee80211_get_key_rx_seq(keyconf, 0, &seq);
		ieee80211_get_tkip_rx_p1k(keyconf, addr, seq.tkip.iv32, p1k);
		ret = iwl_mvm_send_sta_key(mvm, mvm_sta, keyconf, sta_id,
					   seq.tkip.iv32, p1k, CMD_SYNC);
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		ret = iwl_mvm_send_sta_key(mvm, mvm_sta, keyconf, sta_id,
					   0, NULL, CMD_SYNC);
		break;
	default:
		IWL_ERR(mvm, "Unknown cipher %x\n", keyconf->cipher);
		ret = -EINVAL;
	}

	if (ret)
		__clear_bit(keyconf->hw_key_idx, mvm->fw_key_table);

end:
	IWL_DEBUG_WEP(mvm, "key: cipher=%x len=%d idx=%d sta=%pM ret=%d\n",
		      keyconf->cipher, keyconf->keylen, keyconf->keyidx,
		      sta->addr, ret);
	return ret;
}