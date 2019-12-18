#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int control_port; int /*<<< orphan*/  control_port_ethertype; } ;
struct TYPE_5__ {size_t ssid_len; TYPE_1__ crypto; scalar_t__ ssid; } ;
struct TYPE_6__ {int prev_bssid_valid; TYPE_2__ connect; scalar_t__ ssid; } ;
struct wireless_dev {scalar_t__ iftype; scalar_t__ sme_state; TYPE_3__ wext; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {size_t length; int /*<<< orphan*/  flags; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  sched_scan_mtx; } ;

/* Variables and functions */
 scalar_t__ CFG80211_SME_IDLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int __cfg80211_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_lock_rdev (struct cfg80211_registered_device*) ; 
 int cfg80211_mgd_wext_connect (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

int cfg80211_mgd_wext_siwessid(struct net_device *dev,
			       struct iw_request_info *info,
			       struct iw_point *data, char *ssid)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	size_t len = data->length;
	int err;

	/* call only for station! */
	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_STATION))
		return -EINVAL;

	if (!data->flags)
		len = 0;

	/* iwconfig uses nul termination in SSID.. */
	if (len > 0 && ssid[len - 1] == '\0')
		len--;

	cfg80211_lock_rdev(rdev);
	mutex_lock(&rdev->devlist_mtx);
	mutex_lock(&rdev->sched_scan_mtx);
	wdev_lock(wdev);

	err = 0;

	if (wdev->sme_state != CFG80211_SME_IDLE) {
		bool event = true;

		if (wdev->wext.connect.ssid && len &&
		    len == wdev->wext.connect.ssid_len &&
		    memcmp(wdev->wext.connect.ssid, ssid, len) == 0)
			goto out;

		/* if SSID set now, we'll try to connect, avoid event */
		if (len)
			event = false;
		err = __cfg80211_disconnect(rdev, dev,
					    WLAN_REASON_DEAUTH_LEAVING, event);
		if (err)
			goto out;
	}

	wdev->wext.prev_bssid_valid = false;
	wdev->wext.connect.ssid = wdev->wext.ssid;
	memcpy(wdev->wext.ssid, ssid, len);
	wdev->wext.connect.ssid_len = len;

	wdev->wext.connect.crypto.control_port = false;
	wdev->wext.connect.crypto.control_port_ethertype =
					cpu_to_be16(ETH_P_PAE);

	err = cfg80211_mgd_wext_connect(rdev, wdev);
 out:
	wdev_unlock(wdev);
	mutex_unlock(&rdev->sched_scan_mtx);
	mutex_unlock(&rdev->devlist_mtx);
	cfg80211_unlock_rdev(rdev);
	return err;
}