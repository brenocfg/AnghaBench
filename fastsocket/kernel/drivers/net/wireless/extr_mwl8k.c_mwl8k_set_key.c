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
struct mwl8k_vif {int is_hw_crypto_enabled; } ;
struct mwl8k_priv {int /*<<< orphan*/  ap_fw; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/ * addr; } ;
struct ieee80211_sta {int /*<<< orphan*/ * addr; } ;
struct ieee80211_key_conf {scalar_t__ cipher; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MWL8K_UPDATE_ENCRYPTION_TYPE_MIXED ; 
 int /*<<< orphan*/  MWL8K_UPDATE_ENCRYPTION_TYPE_WEP ; 
 struct mwl8k_vif* MWL8K_VIF (struct ieee80211_vif*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int SET_KEY ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int mwl8k_cmd_encryption_remove_key (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,struct ieee80211_key_conf*) ; 
 int mwl8k_cmd_encryption_set_key (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,struct ieee80211_key_conf*) ; 
 int mwl8k_cmd_update_encryption_enable (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwl8k_set_key(struct ieee80211_hw *hw,
			 enum set_key_cmd cmd_param,
			 struct ieee80211_vif *vif,
			 struct ieee80211_sta *sta,
			 struct ieee80211_key_conf *key)
{
	int rc = 0;
	u8 encr_type;
	u8 *addr;
	struct mwl8k_vif *mwl8k_vif = MWL8K_VIF(vif);
	struct mwl8k_priv *priv = hw->priv;

	if (vif->type == NL80211_IFTYPE_STATION && !priv->ap_fw)
		return -EOPNOTSUPP;

	if (sta == NULL)
		addr = vif->addr;
	else
		addr = sta->addr;

	if (cmd_param == SET_KEY) {
		rc = mwl8k_cmd_encryption_set_key(hw, vif, addr, key);
		if (rc)
			goto out;

		if ((key->cipher == WLAN_CIPHER_SUITE_WEP40)
				|| (key->cipher == WLAN_CIPHER_SUITE_WEP104))
			encr_type = MWL8K_UPDATE_ENCRYPTION_TYPE_WEP;
		else
			encr_type = MWL8K_UPDATE_ENCRYPTION_TYPE_MIXED;

		rc = mwl8k_cmd_update_encryption_enable(hw, vif, addr,
								encr_type);
		if (rc)
			goto out;

		mwl8k_vif->is_hw_crypto_enabled = true;

	} else {
		rc = mwl8k_cmd_encryption_remove_key(hw, vif, addr, key);

		if (rc)
			goto out;
	}
out:
	return rc;
}