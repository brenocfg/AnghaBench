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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int bg_scan_period; int privacy; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; } ;
struct TYPE_6__ {int default_key; TYPE_4__ connect; int /*<<< orphan*/ * prev_bssid; scalar_t__ prev_bssid_valid; TYPE_3__* keys; int /*<<< orphan*/  default_mgmt_key; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; } ;
struct wireless_dev {TYPE_2__ wext; int /*<<< orphan*/  netdev; } ;
struct cfg80211_registered_device {int dummy; } ;
struct cfg80211_cached_keys {int /*<<< orphan*/ * data; TYPE_1__* params; } ;
struct TYPE_7__ {int def; int /*<<< orphan*/  defmgmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RDEV_LOCK (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __cfg80211_connect (struct cfg80211_registered_device*,int /*<<< orphan*/ ,TYPE_4__*,struct cfg80211_cached_keys*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_cached_keys*) ; 
 struct cfg80211_cached_keys* kmemdup (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

int cfg80211_mgd_wext_connect(struct cfg80211_registered_device *rdev,
			      struct wireless_dev *wdev)
{
	struct cfg80211_cached_keys *ck = NULL;
	const u8 *prev_bssid = NULL;
	int err, i;

	ASSERT_RDEV_LOCK(rdev);
	ASSERT_WDEV_LOCK(wdev);

	if (!netif_running(wdev->netdev))
		return 0;

	wdev->wext.connect.ie = wdev->wext.ie;
	wdev->wext.connect.ie_len = wdev->wext.ie_len;

	/* Use default background scan period */
	wdev->wext.connect.bg_scan_period = -1;

	if (wdev->wext.keys) {
		wdev->wext.keys->def = wdev->wext.default_key;
		wdev->wext.keys->defmgmt = wdev->wext.default_mgmt_key;
		if (wdev->wext.default_key != -1)
			wdev->wext.connect.privacy = true;
	}

	if (!wdev->wext.connect.ssid_len)
		return 0;

	if (wdev->wext.keys) {
		ck = kmemdup(wdev->wext.keys, sizeof(*ck), GFP_KERNEL);
		if (!ck)
			return -ENOMEM;
		for (i = 0; i < 6; i++)
			ck->params[i].key = ck->data[i];
	}

	if (wdev->wext.prev_bssid_valid)
		prev_bssid = wdev->wext.prev_bssid;

	err = __cfg80211_connect(rdev, wdev->netdev,
				 &wdev->wext.connect, ck, prev_bssid);
	if (err)
		kfree(ck);

	return err;
}