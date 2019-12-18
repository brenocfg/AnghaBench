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
struct cfg80211_chan_def {int dummy; } ;
struct wireless_dev {int iftype; struct cfg80211_chan_def preset_chandef; int /*<<< orphan*/  beacon_interval; } ;
struct genl_info {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_mtx; int /*<<< orphan*/  wiphy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_P2P_GO 128 
 int /*<<< orphan*/  cfg80211_reg_can_beacon (int /*<<< orphan*/ *,struct cfg80211_chan_def*) ; 
 int cfg80211_set_mesh_channel (struct cfg80211_registered_device*,struct wireless_dev*,struct cfg80211_chan_def*) ; 
 int cfg80211_set_monitor_channel (struct cfg80211_registered_device*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_can_set_dev_channel (struct wireless_dev*) ; 
 int nl80211_parse_chandef (struct cfg80211_registered_device*,struct genl_info*,struct cfg80211_chan_def*) ; 

__attribute__((used)) static int __nl80211_set_channel(struct cfg80211_registered_device *rdev,
				 struct wireless_dev *wdev,
				 struct genl_info *info)
{
	struct cfg80211_chan_def chandef;
	int result;
	enum nl80211_iftype iftype = NL80211_IFTYPE_MONITOR;

	if (wdev)
		iftype = wdev->iftype;

	if (!nl80211_can_set_dev_channel(wdev))
		return -EOPNOTSUPP;

	result = nl80211_parse_chandef(rdev, info, &chandef);
	if (result)
		return result;

	mutex_lock(&rdev->devlist_mtx);
	switch (iftype) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
		if (wdev->beacon_interval) {
			result = -EBUSY;
			break;
		}
		if (!cfg80211_reg_can_beacon(&rdev->wiphy, &chandef)) {
			result = -EINVAL;
			break;
		}
		wdev->preset_chandef = chandef;
		result = 0;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		result = cfg80211_set_mesh_channel(rdev, wdev, &chandef);
		break;
	case NL80211_IFTYPE_MONITOR:
		result = cfg80211_set_monitor_channel(rdev, &chandef);
		break;
	default:
		result = -EINVAL;
	}
	mutex_unlock(&rdev->devlist_mtx);

	return result;
}