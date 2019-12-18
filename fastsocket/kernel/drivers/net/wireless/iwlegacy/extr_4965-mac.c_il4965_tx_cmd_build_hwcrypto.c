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
struct il_tx_cmd {int sec_ctl; int /*<<< orphan*/ * key; int /*<<< orphan*/  tx_flags; } ;
struct il_priv {int dummy; } ;
struct TYPE_2__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_key_conf {int cipher; int keyidx; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TX (char*,...) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  TX_CMD_FLG_AGG_CCMP_MSK ; 
 int TX_CMD_SEC_CCM ; 
 int TX_CMD_SEC_KEY128 ; 
 int TX_CMD_SEC_MSK ; 
 int TX_CMD_SEC_SHIFT ; 
 int TX_CMD_SEC_TKIP ; 
 int TX_CMD_SEC_WEP ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  ieee80211_get_tkip_p2k (struct ieee80211_key_conf*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_tx_cmd_build_hwcrypto(struct il_priv *il, struct ieee80211_tx_info *info,
			     struct il_tx_cmd *tx_cmd, struct sk_buff *skb_frag,
			     int sta_id)
{
	struct ieee80211_key_conf *keyconf = info->control.hw_key;

	switch (keyconf->cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
		tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
		memcpy(tx_cmd->key, keyconf->key, keyconf->keylen);
		if (info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_cmd->tx_flags |= TX_CMD_FLG_AGG_CCMP_MSK;
		D_TX("tx_cmd with AES hwcrypto\n");
		break;

	case WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		D_TX("tx_cmd with tkip hwcrypto\n");
		break;

	case WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		/* fall through */
	case WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |=
		    (TX_CMD_SEC_WEP | (keyconf->keyidx & TX_CMD_SEC_MSK) <<
		     TX_CMD_SEC_SHIFT);

		memcpy(&tx_cmd->key[3], keyconf->key, keyconf->keylen);

		D_TX("Configuring packet for WEP encryption " "with key %d\n",
		     keyconf->keyidx);
		break;

	default:
		IL_ERR("Unknown encode cipher %x\n", keyconf->cipher);
		break;
	}
}