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
struct wireless_dev {scalar_t__ iftype; int p2p_started; int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  opencount; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ iftype; int p2p_started; int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  opencount; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  start_p2p_device; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int cfg80211_can_add_interface (struct wireless_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdev_start_p2p_device (struct wireless_dev*,struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_start_p2p_device(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	int err;

	if (!rdev->ops->start_p2p_device)
		return -EOPNOTSUPP;

	if (wdev->iftype != NL80211_IFTYPE_P2P_DEVICE)
		return -EOPNOTSUPP;

	if (wdev->p2p_started)
		return 0;

	mutex_lock(&rdev->devlist_mtx);
	err = cfg80211_can_add_interface(rdev, wdev->iftype);
	mutex_unlock(&rdev->devlist_mtx);
	if (err)
		return err;

	err = rdev_start_p2p_device(rdev, wdev);
	if (err)
		return err;

	wdev->p2p_started = true;
	mutex_lock(&rdev->devlist_mtx);
	rdev->opencount++;
	mutex_unlock(&rdev->devlist_mtx);

	return 0;
}