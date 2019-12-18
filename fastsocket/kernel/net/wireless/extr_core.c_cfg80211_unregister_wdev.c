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
struct wireless_dev {int iftype; int /*<<< orphan*/  list; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  sched_scan_mtx; int /*<<< orphan*/  devlist_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_stop_p2p_device (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

void cfg80211_unregister_wdev(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);

	ASSERT_RTNL();

	if (WARN_ON(wdev->netdev))
		return;

	mutex_lock(&rdev->devlist_mtx);
	mutex_lock(&rdev->sched_scan_mtx);
	list_del_rcu(&wdev->list);
	rdev->devlist_generation++;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_P2P_DEVICE:
		cfg80211_stop_p2p_device(rdev, wdev);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}
	mutex_unlock(&rdev->sched_scan_mtx);
	mutex_unlock(&rdev->devlist_mtx);
}