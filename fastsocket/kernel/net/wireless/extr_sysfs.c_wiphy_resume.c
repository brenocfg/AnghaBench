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
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ registered; } ;
struct cfg80211_registered_device {TYPE_2__ wiphy; TYPE_1__* ops; scalar_t__ suspend_at; } ;
struct TYPE_3__ {scalar_t__ resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_bss_age (struct cfg80211_registered_device*,scalar_t__) ; 
 struct cfg80211_registered_device* dev_to_rdev (struct device*) ; 
 scalar_t__ get_seconds () ; 
 int rdev_resume (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int wiphy_resume(struct device *dev)
{
	struct cfg80211_registered_device *rdev = dev_to_rdev(dev);
	int ret = 0;

	/* Age scan results with time spent in suspend */
	cfg80211_bss_age(rdev, get_seconds() - rdev->suspend_at);

	if (rdev->ops->resume) {
		rtnl_lock();
		if (rdev->wiphy.registered)
			ret = rdev_resume(rdev);
		rtnl_unlock();
	}

	return ret;
}