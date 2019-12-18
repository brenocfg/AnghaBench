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
struct sk_buff {int dummy; } ;
struct iwl_tx_cmd {int sec_ctl; int /*<<< orphan*/ * key; int /*<<< orphan*/  tx_flags; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_key_conf {int cipher; int keyidx; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  TX_CMD_FLG_CCMP_AGG ; 
 int TX_CMD_SEC_CCM ; 
 int TX_CMD_SEC_KEY128 ; 
 int TX_CMD_SEC_TKIP ; 
 int TX_CMD_SEC_WEP ; 
 int TX_CMD_SEC_WEP_KEY_IDX_MSK ; 
 int TX_CMD_SEC_WEP_KEY_IDX_POS ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_tkip_p2k (struct ieee80211_key_conf*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_set_tx_cmd_crypto(struct iwl_mvm *mvm,
				      struct ieee80211_tx_info *info,
				      struct iwl_tx_cmd *tx_cmd,
				      struct sk_buff *skb_frag)
{
	struct ieee80211_key_conf *keyconf = info->control.hw_key;

	switch (keyconf->cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
		tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
		memcpy(tx_cmd->key, keyconf->key, keyconf->keylen);
		if (info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_cmd->tx_flags |= cpu_to_le32(TX_CMD_FLG_CCMP_AGG);
		break;

	case WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		break;

	case WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		/* fall through */
	case WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |= TX_CMD_SEC_WEP |
			((keyconf->keyidx << TX_CMD_SEC_WEP_KEY_IDX_POS) &
			  TX_CMD_SEC_WEP_KEY_IDX_MSK);

		memcpy(&tx_cmd->key[3], keyconf->key, keyconf->keylen);
		break;
	default:
		IWL_ERR(mvm, "Unknown encode cipher %x\n", keyconf->cipher);
		break;
	}
}