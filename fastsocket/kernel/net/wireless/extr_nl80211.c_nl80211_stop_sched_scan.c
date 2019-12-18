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
struct sk_buff {int dummy; } ;
struct genl_info {struct cfg80211_registered_device** user_ptr; } ;
struct TYPE_3__ {int flags; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  sched_scan_mtx; TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched_scan_stop; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WIPHY_FLAG_SUPPORTS_SCHED_SCAN ; 
 int __cfg80211_stop_sched_scan (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_stop_sched_scan(struct sk_buff *skb,
				   struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	int err;

	if (!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_SCHED_SCAN) ||
	    !rdev->ops->sched_scan_stop)
		return -EOPNOTSUPP;

	mutex_lock(&rdev->sched_scan_mtx);
	err = __cfg80211_stop_sched_scan(rdev, false);
	mutex_unlock(&rdev->sched_scan_mtx);

	return err;
}