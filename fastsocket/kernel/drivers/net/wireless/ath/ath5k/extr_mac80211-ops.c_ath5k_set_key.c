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
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int flags; int cipher; int hw_key_idx; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath_common {int crypt_caps; } ;
struct ath5k_hw {int /*<<< orphan*/  lock; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int ATH_CRYPT_CAP_CIPHER_AESCCM ; 
#define  DISABLE_KEY 133 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_RX_MGMT ; 
 int IEEE80211_KEY_FLAG_SW_MGMT_TX ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
#define  SET_KEY 132 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 scalar_t__ ath5k_modparam_nohwcrypt ; 
 int ath_key_config (struct ath_common*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  ath_key_delete (struct ath_common*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath5k_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
	      struct ieee80211_vif *vif, struct ieee80211_sta *sta,
	      struct ieee80211_key_conf *key)
{
	struct ath5k_hw *ah = hw->priv;
	struct ath_common *common = ath5k_hw_common(ah);
	int ret = 0;

	if (ath5k_modparam_nohwcrypt)
		return -EOPNOTSUPP;

	if (key->flags & IEEE80211_KEY_FLAG_RX_MGMT)
		return -EOPNOTSUPP;

	if (vif->type == NL80211_IFTYPE_ADHOC &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
		/* don't program group keys when using IBSS_RSN */
		return -EOPNOTSUPP;
	}

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
	case WLAN_CIPHER_SUITE_TKIP:
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		if (common->crypt_caps & ATH_CRYPT_CAP_CIPHER_AESCCM)
			break;
		return -EOPNOTSUPP;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	mutex_lock(&ah->lock);

	switch (cmd) {
	case SET_KEY:
		ret = ath_key_config(common, vif, sta, key);
		if (ret >= 0) {
			key->hw_key_idx = ret;
			/* push IV and Michael MIC generation to stack */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			if (key->cipher == WLAN_CIPHER_SUITE_TKIP)
				key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			if (key->cipher == WLAN_CIPHER_SUITE_CCMP)
				key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			ret = 0;
		}
		break;
	case DISABLE_KEY:
		ath_key_delete(common, key);
		break;
	default:
		ret = -EINVAL;
	}

	mmiowb();
	mutex_unlock(&ah->lock);
	return ret;
}