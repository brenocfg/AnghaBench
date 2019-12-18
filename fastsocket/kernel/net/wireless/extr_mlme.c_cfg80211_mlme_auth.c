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
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; } ;
typedef  enum nl80211_auth_type { ____Placeholder_nl80211_auth_type } nl80211_auth_type ;

/* Variables and functions */
 int __cfg80211_mlme_auth (struct cfg80211_registered_device*,struct net_device*,struct ieee80211_channel*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_unlock (int /*<<< orphan*/ ) ; 

int cfg80211_mlme_auth(struct cfg80211_registered_device *rdev,
		       struct net_device *dev, struct ieee80211_channel *chan,
		       enum nl80211_auth_type auth_type, const u8 *bssid,
		       const u8 *ssid, int ssid_len,
		       const u8 *ie, int ie_len,
		       const u8 *key, int key_len, int key_idx,
		       const u8 *sae_data, int sae_data_len)
{
	int err;

	mutex_lock(&rdev->devlist_mtx);
	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_mlme_auth(rdev, dev, chan, auth_type, bssid,
				   ssid, ssid_len, ie, ie_len,
				   key, key_len, key_idx,
				   sae_data, sae_data_len);
	wdev_unlock(dev->ieee80211_ptr);
	mutex_unlock(&rdev->devlist_mtx);

	return err;
}