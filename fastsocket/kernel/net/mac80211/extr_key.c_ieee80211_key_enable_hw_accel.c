#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_5__ sta; int /*<<< orphan*/  uploaded; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  crypto_tx_tailroom_needed_cnt; TYPE_3__ vif; } ;
struct TYPE_13__ {int flags; int cipher; int /*<<< orphan*/  keyidx; } ;
struct ieee80211_key {TYPE_6__ conf; int /*<<< orphan*/  flags; TYPE_4__* local; struct ieee80211_sub_if_data* sdata; struct sta_info* sta; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_11__ {TYPE_2__ hw; TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  set_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int IEEE80211_HW_SUPPORTS_PER_STA_GTK ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 int /*<<< orphan*/  KEY_FLAG_UPLOADED_TO_HARDWARE ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  SET_KEY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  assert_key_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  bcast_addr ; 
 int drv_set_key (TYPE_4__*,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  sdata_err (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_key_enable_hw_accel(struct ieee80211_key *key)
{
	struct ieee80211_sub_if_data *sdata;
	struct sta_info *sta;
	int ret;

	might_sleep();

	if (!key->local->ops->set_key)
		goto out_unsupported;

	assert_key_lock(key->local);

	sta = key->sta;

	/*
	 * If this is a per-STA GTK, check if it
	 * is supported; if not, return.
	 */
	if (sta && !(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE) &&
	    !(key->local->hw.flags & IEEE80211_HW_SUPPORTS_PER_STA_GTK))
		goto out_unsupported;

	if (sta && !sta->uploaded)
		goto out_unsupported;

	sdata = key->sdata;
	if (sdata->vif.type == NL80211_IFTYPE_AP_VLAN) {
		/*
		 * The driver doesn't know anything about VLAN interfaces.
		 * Hence, don't send GTKs for VLAN interfaces to the driver.
		 */
		if (!(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE))
			goto out_unsupported;
	}

	ret = drv_set_key(key->local, SET_KEY, sdata,
			  sta ? &sta->sta : NULL, &key->conf);

	if (!ret) {
		key->flags |= KEY_FLAG_UPLOADED_TO_HARDWARE;

		if (!((key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_MMIC) ||
		      (key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV) ||
		      (key->conf.flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE)))
			sdata->crypto_tx_tailroom_needed_cnt--;

		WARN_ON((key->conf.flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE) &&
			(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV));

		return 0;
	}

	if (ret != -ENOSPC && ret != -EOPNOTSUPP)
		sdata_err(sdata,
			  "failed to set key (%d, %pM) to hardware (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addr : bcast_addr, ret);

 out_unsupported:
	switch (key->conf.cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_AES_CMAC:
		/* all of these we can do in software */
		return 0;
	default:
		return -EINVAL;
	}
}