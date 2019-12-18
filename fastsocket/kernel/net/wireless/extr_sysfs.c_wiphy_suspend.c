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
struct TYPE_3__ {scalar_t__ registered; } ;
struct cfg80211_registered_device {int /*<<< orphan*/ * wowlan; TYPE_2__* ops; TYPE_1__ wiphy; int /*<<< orphan*/  suspend_at; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_4__ {scalar_t__ suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_leave_all (struct cfg80211_registered_device*) ; 
 struct cfg80211_registered_device* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int rdev_suspend (struct cfg80211_registered_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int wiphy_suspend(struct device *dev, pm_message_t state)
{
	struct cfg80211_registered_device *rdev = dev_to_rdev(dev);
	int ret = 0;

	rdev->suspend_at = get_seconds();

	rtnl_lock();
	if (rdev->wiphy.registered) {
		if (!rdev->wowlan)
			cfg80211_leave_all(rdev);
		if (rdev->ops->suspend)
			ret = rdev_suspend(rdev, rdev->wowlan);
		if (ret == 1) {
			/* Driver refuse to configure wowlan */
			cfg80211_leave_all(rdev);
			ret = rdev_suspend(rdev, NULL);
		}
	}
	rtnl_unlock();

	return ret;
}