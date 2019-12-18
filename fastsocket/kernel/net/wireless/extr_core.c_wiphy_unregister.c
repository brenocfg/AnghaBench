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
struct wiphy {int dummy; } ;
struct TYPE_3__ {int registered; int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfsdir; } ;
struct cfg80211_registered_device {int opencount; TYPE_2__* ops; scalar_t__ wowlan; int /*<<< orphan*/  dfs_update_channels_wk; int /*<<< orphan*/  event_work; int /*<<< orphan*/  conn_work; int /*<<< orphan*/  scan_done_wk; TYPE_1__ wiphy; int /*<<< orphan*/  list; int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  wdev_list; int /*<<< orphan*/  dev_wait; int /*<<< orphan*/  rfkill; } ;
struct TYPE_4__ {scalar_t__ set_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_lock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_mutex ; 
 int /*<<< orphan*/  cfg80211_rdev_free_wowlan (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_rdev_list_generation ; 
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_set_wakeup (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_regulatory_deregister (struct wiphy*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

void wiphy_unregister(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);

	rtnl_lock();
	rdev->wiphy.registered = false;
	rtnl_unlock();

	rfkill_unregister(rdev->rfkill);

	/* protect the device list */
	mutex_lock(&cfg80211_mutex);

	wait_event(rdev->dev_wait, ({
		int __count;
		mutex_lock(&rdev->devlist_mtx);
		__count = rdev->opencount;
		mutex_unlock(&rdev->devlist_mtx);
		__count == 0; }));

	mutex_lock(&rdev->devlist_mtx);
	BUG_ON(!list_empty(&rdev->wdev_list));
	mutex_unlock(&rdev->devlist_mtx);

	/*
	 * First remove the hardware from everywhere, this makes
	 * it impossible to find from userspace.
	 */
	debugfs_remove_recursive(rdev->wiphy.debugfsdir);
	list_del_rcu(&rdev->list);
	synchronize_rcu();

	/*
	 * Try to grab rdev->mtx. If a command is still in progress,
	 * hopefully the driver will refuse it since it's tearing
	 * down the device already. We wait for this command to complete
	 * before unlinking the item from the list.
	 * Note: as codified by the BUG_ON above we cannot get here if
	 * a virtual interface is still present. Hence, we can only get
	 * to lock contention here if userspace issues a command that
	 * identified the hardware by wiphy index.
	 */
	cfg80211_lock_rdev(rdev);
	/* nothing */
	cfg80211_unlock_rdev(rdev);

	/*
	 * If this device got a regulatory hint tell core its
	 * free to listen now to a new shiny device regulatory hint
	 */
	wiphy_regulatory_deregister(wiphy);

	cfg80211_rdev_list_generation++;
	device_del(&rdev->wiphy.dev);

	mutex_unlock(&cfg80211_mutex);

	flush_work(&rdev->scan_done_wk);
	cancel_work_sync(&rdev->conn_work);
	flush_work(&rdev->event_work);
	cancel_delayed_work_sync(&rdev->dfs_update_channels_wk);

	if (rdev->wowlan && rdev->ops->set_wakeup)
		rdev_set_wakeup(rdev, false);
	cfg80211_rdev_free_wowlan(rdev);
}