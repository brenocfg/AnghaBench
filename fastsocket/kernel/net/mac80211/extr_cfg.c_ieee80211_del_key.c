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
typedef  size_t u8 ;
struct wiphy {int dummy; } ;
struct sta_info {int /*<<< orphan*/ * gtk; int /*<<< orphan*/  ptk; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/ * keys; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; int /*<<< orphan*/  key_mtx; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_key_free (struct ieee80211_key*,int) ; 
 struct ieee80211_key* key_mtx_dereference (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,size_t const*) ; 

__attribute__((used)) static int ieee80211_del_key(struct wiphy *wiphy, struct net_device *dev,
			     u8 key_idx, bool pairwise, const u8 *mac_addr)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct ieee80211_key *key = NULL;
	int ret;

	mutex_lock(&local->sta_mtx);
	mutex_lock(&local->key_mtx);

	if (mac_addr) {
		ret = -ENOENT;

		sta = sta_info_get_bss(sdata, mac_addr);
		if (!sta)
			goto out_unlock;

		if (pairwise)
			key = key_mtx_dereference(local, sta->ptk);
		else
			key = key_mtx_dereference(local, sta->gtk[key_idx]);
	} else
		key = key_mtx_dereference(local, sdata->keys[key_idx]);

	if (!key) {
		ret = -ENOENT;
		goto out_unlock;
	}

	ieee80211_key_free(key, true);

	ret = 0;
 out_unlock:
	mutex_unlock(&local->key_mtx);
	mutex_unlock(&local->sta_mtx);

	return ret;
}