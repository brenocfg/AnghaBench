#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct cfg80211_registered_device {TYPE_1__* sched_scan_req; int /*<<< orphan*/  sched_scan_mtx; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NL80211_CMD_SCHED_SCAN_STOPPED ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_send_sched_scan (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ) ; 
 int rdev_sched_scan_stop (struct cfg80211_registered_device*,struct net_device*) ; 

int __cfg80211_stop_sched_scan(struct cfg80211_registered_device *rdev,
			       bool driver_initiated)
{
	struct net_device *dev;

	lockdep_assert_held(&rdev->sched_scan_mtx);

	if (!rdev->sched_scan_req)
		return -ENOENT;

	dev = rdev->sched_scan_req->dev;

	if (!driver_initiated) {
		int err = rdev_sched_scan_stop(rdev, dev);
		if (err)
			return err;
	}

	nl80211_send_sched_scan(rdev, dev, NL80211_CMD_SCHED_SCAN_STOPPED);

	kfree(rdev->sched_scan_req);
	rdev->sched_scan_req = NULL;

	return 0;
}