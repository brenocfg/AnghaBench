#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  auth_type; } ;
struct TYPE_4__ {TYPE_1__ connect; int /*<<< orphan*/  ie_len; int /*<<< orphan*/ * ie; } ;
struct wireless_dev {int iftype; scalar_t__ beacon_interval; TYPE_2__ wext; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  sched_scan_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_AUTHTYPE_AUTOMATIC ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  __cfg80211_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __cfg80211_stop_sched_scan (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  cfg80211_leave_ibss (struct cfg80211_registered_device*,struct net_device*,int) ; 
 int /*<<< orphan*/  cfg80211_leave_mesh (struct cfg80211_registered_device*,struct net_device*) ; 
 int /*<<< orphan*/  cfg80211_stop_ap (struct cfg80211_registered_device*,struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

void cfg80211_leave(struct cfg80211_registered_device *rdev,
		   struct wireless_dev *wdev)
{
	struct net_device *dev = wdev->netdev;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_ADHOC:
		cfg80211_leave_ibss(rdev, dev, true);
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_STATION:
		mutex_lock(&rdev->sched_scan_mtx);
		__cfg80211_stop_sched_scan(rdev, false);
		mutex_unlock(&rdev->sched_scan_mtx);

		wdev_lock(wdev);
#ifdef CONFIG_CFG80211_WEXT
		kfree(wdev->wext.ie);
		wdev->wext.ie = NULL;
		wdev->wext.ie_len = 0;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;
#endif
		__cfg80211_disconnect(rdev, dev,
				      WLAN_REASON_DEAUTH_LEAVING, true);
		wdev_unlock(wdev);
		break;
	case NL80211_IFTYPE_MESH_POINT:
		cfg80211_leave_mesh(rdev, dev);
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
		cfg80211_stop_ap(rdev, dev);
		break;
	default:
		break;
	}

	wdev->beacon_interval = 0;
}