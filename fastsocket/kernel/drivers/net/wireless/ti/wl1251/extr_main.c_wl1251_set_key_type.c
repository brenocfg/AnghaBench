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
struct wl1251_cmd_set_keys {int /*<<< orphan*/  key_type; } ;
struct wl1251 {int dummy; } ;
struct ieee80211_key_conf {int cipher; int /*<<< orphan*/  flags; int /*<<< orphan*/  keyidx; int /*<<< orphan*/  hw_key_idx; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int /*<<< orphan*/  KEY_AES_GROUP ; 
 int /*<<< orphan*/  KEY_AES_PAIRWISE ; 
 int /*<<< orphan*/  KEY_TKIP_MIC_GROUP ; 
 int /*<<< orphan*/  KEY_TKIP_MIC_PAIRWISE ; 
 int /*<<< orphan*/  KEY_WEP_ADDR ; 
 int /*<<< orphan*/  KEY_WEP_DEFAULT ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 

__attribute__((used)) static int wl1251_set_key_type(struct wl1251 *wl,
			       struct wl1251_cmd_set_keys *key,
			       enum set_key_cmd cmd,
			       struct ieee80211_key_conf *mac80211_key,
			       const u8 *addr)
{
	switch (mac80211_key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		if (is_broadcast_ether_addr(addr))
			key->key_type = KEY_WEP_DEFAULT;
		else
			key->key_type = KEY_WEP_ADDR;

		mac80211_key->hw_key_idx = mac80211_key->keyidx;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		if (is_broadcast_ether_addr(addr))
			key->key_type = KEY_TKIP_MIC_GROUP;
		else
			key->key_type = KEY_TKIP_MIC_PAIRWISE;

		mac80211_key->hw_key_idx = mac80211_key->keyidx;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		if (is_broadcast_ether_addr(addr))
			key->key_type = KEY_AES_GROUP;
		else
			key->key_type = KEY_AES_PAIRWISE;
		mac80211_key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		break;
	default:
		wl1251_error("Unknown key cipher 0x%x", mac80211_key->cipher);
		return -EOPNOTSUPP;
	}

	return 0;
}