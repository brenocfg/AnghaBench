#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* wep_keys; } ;
struct il_priv {TYPE_4__ _4965; TYPE_2__* stations; int /*<<< orphan*/  mutex; } ;
struct ieee80211_key_conf {int keylen; int keyidx; int /*<<< orphan*/  key; int /*<<< orphan*/  cipher; int /*<<< orphan*/  hw_key_idx; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int key_size; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int /*<<< orphan*/  cipher; } ;
struct TYPE_6__ {TYPE_1__ keyinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEP (char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HW_KEY_DEFAULT ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 size_t IL_AP_ID ; 
 int WEP_KEY_LEN_128 ; 
 int WEP_KEY_LEN_64 ; 
 int il4965_static_wepkey_cmd (struct il_priv*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
il4965_set_default_wep_key(struct il_priv *il,
			   struct ieee80211_key_conf *keyconf)
{
	int ret;
	int len = keyconf->keylen;
	int idx = keyconf->keyidx;

	lockdep_assert_held(&il->mutex);

	if (len != WEP_KEY_LEN_128 && len != WEP_KEY_LEN_64) {
		D_WEP("Bad WEP key length %d\n", keyconf->keylen);
		return -EINVAL;
	}

	keyconf->flags &= ~IEEE80211_KEY_FLAG_GENERATE_IV;
	keyconf->hw_key_idx = HW_KEY_DEFAULT;
	il->stations[IL_AP_ID].keyinfo.cipher = keyconf->cipher;

	il->_4965.wep_keys[idx].key_size = len;
	memcpy(&il->_4965.wep_keys[idx].key, &keyconf->key, len);

	ret = il4965_static_wepkey_cmd(il, false);

	D_WEP("Set default WEP key: len=%d idx=%d ret=%d\n", len, idx, ret);
	return ret;
}