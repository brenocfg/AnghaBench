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
struct iwl_vif_priv {struct iwl_rxon_context* ctx; } ;
struct iwl_rxon_context {int /*<<< orphan*/  key_mapping_keys; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int cipher; int flags; scalar_t__ hw_key_idx; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_2__ {scalar_t__ sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  DISABLE_KEY 131 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ IWLAGN_HW_KEY_DEFAULT ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
#define  SET_KEY 130 
 scalar_t__ WEP_INVALID_OFFSET ; 
#define  WLAN_CIPHER_SUITE_CCMP 129 
#define  WLAN_CIPHER_SUITE_TKIP 128 
 int WLAN_CIPHER_SUITE_WEP104 ; 
 int WLAN_CIPHER_SUITE_WEP40 ; 
 int iwl_remove_default_wep_key (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_key_conf*) ; 
 int iwl_remove_dynamic_key (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_key_conf*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_scan_cancel_timeout (struct iwl_priv*,int) ; 
 int iwl_set_default_wep_key (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_key_conf*) ; 
 int iwl_set_dynamic_key (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_key_conf*,struct ieee80211_sta*) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
			      struct ieee80211_vif *vif,
			      struct ieee80211_sta *sta,
			      struct ieee80211_key_conf *key)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_vif_priv *vif_priv = (void *)vif->drv_priv;
	struct iwl_rxon_context *ctx = vif_priv->ctx;
	int ret;
	bool is_default_wep_key = false;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	if (iwlwifi_mod_params.sw_crypto) {
		IWL_DEBUG_MAC80211(priv, "leave - hwcrypto disabled\n");
		return -EOPNOTSUPP;
	}

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		/* fall through */
	case WLAN_CIPHER_SUITE_CCMP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		break;
	default:
		break;
	}

	/*
	 * We could program these keys into the hardware as well, but we
	 * don't expect much multicast traffic in IBSS and having keys
	 * for more stations is probably more useful.
	 *
	 * Mark key TX-only and return 0.
	 */
	if (vif->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
		key->hw_key_idx = WEP_INVALID_OFFSET;
		return 0;
	}

	/* If they key was TX-only, accept deletion */
	if (cmd == DISABLE_KEY && key->hw_key_idx == WEP_INVALID_OFFSET)
		return 0;

	mutex_lock(&priv->mutex);
	iwl_scan_cancel_timeout(priv, 100);

	BUILD_BUG_ON(WEP_INVALID_OFFSET == IWLAGN_HW_KEY_DEFAULT);

	/*
	 * If we are getting WEP group key and we didn't receive any key mapping
	 * so far, we are in legacy wep mode (group key only), otherwise we are
	 * in 1X mode.
	 * In legacy wep mode, we use another host command to the uCode.
	 */
	if ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     key->cipher == WLAN_CIPHER_SUITE_WEP104) && !sta) {
		if (cmd == SET_KEY)
			is_default_wep_key = !ctx->key_mapping_keys;
		else
			is_default_wep_key =
				key->hw_key_idx == IWLAGN_HW_KEY_DEFAULT;
	}


	switch (cmd) {
	case SET_KEY:
		if (is_default_wep_key) {
			ret = iwl_set_default_wep_key(priv, vif_priv->ctx, key);
			break;
		}
		ret = iwl_set_dynamic_key(priv, vif_priv->ctx, key, sta);
		if (ret) {
			/*
			 * can't add key for RX, but we don't need it
			 * in the device for TX so still return 0
			 */
			ret = 0;
			key->hw_key_idx = WEP_INVALID_OFFSET;
		}

		IWL_DEBUG_MAC80211(priv, "enable hwcrypto key\n");
		break;
	case DISABLE_KEY:
		if (is_default_wep_key)
			ret = iwl_remove_default_wep_key(priv, ctx, key);
		else
			ret = iwl_remove_dynamic_key(priv, ctx, key, sta);

		IWL_DEBUG_MAC80211(priv, "disable hwcrypto key\n");
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	return ret;
}