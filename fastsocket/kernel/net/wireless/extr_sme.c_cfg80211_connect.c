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
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  sched_scan_mtx; } ;
struct cfg80211_connect_params {int dummy; } ;
struct cfg80211_cached_keys {int dummy; } ;

/* Variables and functions */
 int __cfg80211_connect (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_connect_params*,struct cfg80211_cached_keys*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_unlock (int /*<<< orphan*/ ) ; 

int cfg80211_connect(struct cfg80211_registered_device *rdev,
		     struct net_device *dev,
		     struct cfg80211_connect_params *connect,
		     struct cfg80211_cached_keys *connkeys)
{
	int err;

	mutex_lock(&rdev->devlist_mtx);
	/* might request scan - scan_mtx -> wdev_mtx dependency */
	mutex_lock(&rdev->sched_scan_mtx);
	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_connect(rdev, dev, connect, connkeys, NULL);
	wdev_unlock(dev->ieee80211_ptr);
	mutex_unlock(&rdev->sched_scan_mtx);
	mutex_unlock(&rdev->devlist_mtx);

	return err;
}