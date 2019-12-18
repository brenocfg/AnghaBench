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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int cipher; void* hw_key_idx; int /*<<< orphan*/  flags; } ;
struct ieee80211_hw {int flags; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_2__ {scalar_t__ sw_crypto; } ;

/* Variables and functions */
#define  DISABLE_KEY 134 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_HW_MFP_CAPABLE ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
#define  SET_KEY 133 
 void* STA_KEY_IDX_INVALID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int iwl_mvm_remove_sta_key (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int iwl_mvm_set_sta_key (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*,int) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_set_key(struct ieee80211_hw *hw,
			       enum set_key_cmd cmd,
			       struct ieee80211_vif *vif,
			       struct ieee80211_sta *sta,
			       struct ieee80211_key_conf *key)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	if (iwlwifi_mod_params.sw_crypto) {
		IWL_DEBUG_MAC80211(mvm, "leave - hwcrypto disabled\n");
		return -EOPNOTSUPP;
	}

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		/* fall-through */
	case WLAN_CIPHER_SUITE_CCMP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
		WARN_ON_ONCE(!(hw->flags & IEEE80211_HW_MFP_CAPABLE));
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		/*
		 * Support for TX only, at least for now, so accept
		 * the key and do nothing else. Then mac80211 will
		 * pass it for TX but we don't have to use it for RX.
		 */
		return 0;
	default:
		return -EOPNOTSUPP;
	}

	mutex_lock(&mvm->mutex);

	switch (cmd) {
	case SET_KEY:
		if (vif->type == NL80211_IFTYPE_AP && !sta) {
			/* GTK on AP interface is a TX-only key, return 0 */
			ret = 0;
			key->hw_key_idx = STA_KEY_IDX_INVALID;
			break;
		}

		IWL_DEBUG_MAC80211(mvm, "set hwcrypto key\n");
		ret = iwl_mvm_set_sta_key(mvm, vif, sta, key, false);
		if (ret) {
			IWL_WARN(mvm, "set key failed\n");
			/*
			 * can't add key for RX, but we don't need it
			 * in the device for TX so still return 0
			 */
			key->hw_key_idx = STA_KEY_IDX_INVALID;
			ret = 0;
		}

		break;
	case DISABLE_KEY:
		if (key->hw_key_idx == STA_KEY_IDX_INVALID) {
			ret = 0;
			break;
		}

		IWL_DEBUG_MAC80211(mvm, "disable hwcrypto key\n");
		ret = iwl_mvm_remove_sta_key(mvm, vif, sta, key);
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&mvm->mutex);
	return ret;
}