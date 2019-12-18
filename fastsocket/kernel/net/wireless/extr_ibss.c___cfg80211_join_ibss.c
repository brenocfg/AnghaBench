#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {TYPE_6__* chan; } ;
struct TYPE_9__ {TYPE_5__ chandef; } ;
struct TYPE_10__ {TYPE_3__ ibss; } ;
struct wireless_dev {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  sme_state; struct cfg80211_cached_keys* connect_keys; TYPE_4__ wext; scalar_t__ ibss_fixed; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_2__* bitrates; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
struct cfg80211_ibss_params {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; scalar_t__ channel_fixed; TYPE_5__ chandef; int /*<<< orphan*/  basic_rates; } ;
struct cfg80211_cached_keys {int dummy; } ;
struct TYPE_12__ {size_t band; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CFG80211_SME_CONNECTING ; 
 int /*<<< orphan*/  CFG80211_SME_IDLE ; 
 int /*<<< orphan*/  CHAN_MODE_EXCLUSIVE ; 
 int /*<<< orphan*/  CHAN_MODE_SHARED ; 
 int EALREADY ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_RATE_MANDATORY_A ; 
 int IEEE80211_RATE_MANDATORY_B ; 
 scalar_t__ WARN_ON (struct cfg80211_cached_keys*) ; 
 int cfg80211_can_use_chan (struct cfg80211_registered_device*,struct wireless_dev*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_cached_keys*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rdev_join_ibss (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_ibss_params*) ; 

int __cfg80211_join_ibss(struct cfg80211_registered_device *rdev,
			 struct net_device *dev,
			 struct cfg80211_ibss_params *params,
			 struct cfg80211_cached_keys *connkeys)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->ssid_len)
		return -EALREADY;

	if (!params->basic_rates) {
		/*
		* If no rates were explicitly configured,
		* use the mandatory rate set for 11b or
		* 11a for maximum compatibility.
		*/
		struct ieee80211_supported_band *sband =
			rdev->wiphy.bands[params->chandef.chan->band];
		int j;
		u32 flag = params->chandef.chan->band == IEEE80211_BAND_5GHZ ?
			IEEE80211_RATE_MANDATORY_A :
			IEEE80211_RATE_MANDATORY_B;

		for (j = 0; j < sband->n_bitrates; j++) {
			if (sband->bitrates[j].flags & flag)
				params->basic_rates |= BIT(j);
		}
	}

	if (WARN_ON(wdev->connect_keys))
		kfree(wdev->connect_keys);
	wdev->connect_keys = connkeys;

	wdev->ibss_fixed = params->channel_fixed;
#ifdef CONFIG_CFG80211_WEXT
	wdev->wext.ibss.chandef = params->chandef;
#endif
	wdev->sme_state = CFG80211_SME_CONNECTING;

	err = cfg80211_can_use_chan(rdev, wdev, params->chandef.chan,
				    params->channel_fixed
				    ? CHAN_MODE_SHARED
				    : CHAN_MODE_EXCLUSIVE);
	if (err) {
		wdev->connect_keys = NULL;
		return err;
	}

	err = rdev_join_ibss(rdev, dev, params);
	if (err) {
		wdev->connect_keys = NULL;
		wdev->sme_state = CFG80211_SME_IDLE;
		return err;
	}

	memcpy(wdev->ssid, params->ssid, params->ssid_len);
	wdev->ssid_len = params->ssid_len;

	return 0;
}