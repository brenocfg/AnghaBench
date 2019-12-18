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
struct wireless_dev {int cac_started; int /*<<< orphan*/  cac_start_time; TYPE_2__* channel; int /*<<< orphan*/  iftype; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  wiphy; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  wiphy; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_chan_def {TYPE_2__* chan; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {scalar_t__ dfs_state; } ;
struct TYPE_3__ {int (* start_radar_detection ) (int /*<<< orphan*/ *,struct net_device*,struct cfg80211_chan_def*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_MODE_SHARED ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_DFS_USABLE ; 
 int cfg80211_can_use_iftype_chan (struct net_device*,struct wireless_dev*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cfg80211_chandef_dfs_required (int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,struct cfg80211_chan_def*) ; 
 int stub1 (int /*<<< orphan*/ *,struct net_device*,struct cfg80211_chan_def*) ; 

__attribute__((used)) static int nl80211_start_radar_detection(struct sk_buff *skb,
					 struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_chan_def chandef;
	int err;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	if (err)
		return err;

	if (wdev->cac_started)
		return -EBUSY;

	err = cfg80211_chandef_dfs_required(wdev->wiphy, &chandef);
	if (err < 0)
		return err;

	if (err == 0)
		return -EINVAL;

	if (chandef.chan->dfs_state != NL80211_DFS_USABLE)
		return -EINVAL;

	if (!rdev->ops->start_radar_detection)
		return -EOPNOTSUPP;

	mutex_lock(&rdev->devlist_mtx);
	err = cfg80211_can_use_iftype_chan(rdev, wdev, wdev->iftype,
					   chandef.chan, CHAN_MODE_SHARED,
					   BIT(chandef.width));
	if (err)
		goto err_locked;

	err = rdev->ops->start_radar_detection(&rdev->wiphy, dev, &chandef);
	if (!err) {
		wdev->channel = chandef.chan;
		wdev->cac_started = true;
		wdev->cac_start_time = jiffies;
	}
err_locked:
	mutex_unlock(&rdev->devlist_mtx);

	return err;
}