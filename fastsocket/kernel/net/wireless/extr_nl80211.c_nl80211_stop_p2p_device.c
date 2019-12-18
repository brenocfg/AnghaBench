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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  sched_scan_mtx; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ iftype; int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  sched_scan_mtx; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  stop_p2p_device; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  cfg80211_stop_p2p_device (struct wireless_dev*,struct wireless_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_stop_p2p_device(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];

	if (wdev->iftype != NL80211_IFTYPE_P2P_DEVICE)
		return -EOPNOTSUPP;

	if (!rdev->ops->stop_p2p_device)
		return -EOPNOTSUPP;

	mutex_lock(&rdev->devlist_mtx);
	mutex_lock(&rdev->sched_scan_mtx);
	cfg80211_stop_p2p_device(rdev, wdev);
	mutex_unlock(&rdev->sched_scan_mtx);
	mutex_unlock(&rdev->devlist_mtx);

	return 0;
}