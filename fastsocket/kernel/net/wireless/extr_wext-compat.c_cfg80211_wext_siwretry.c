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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {TYPE_1__* wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; void* value; scalar_t__ disabled; } ;
struct cfg80211_registered_device {int dummy; } ;
struct TYPE_2__ {void* retry_long; void* retry_short; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int /*<<< orphan*/  WIPHY_PARAM_RETRY_LONG ; 
 int /*<<< orphan*/  WIPHY_PARAM_RETRY_SHORT ; 
 int rdev_set_wiphy_params (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_dev (TYPE_1__*) ; 

__attribute__((used)) static int cfg80211_wext_siwretry(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_param *retry, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	u32 changed = 0;
	u8 olong = wdev->wiphy->retry_long;
	u8 oshort = wdev->wiphy->retry_short;
	int err;

	if (retry->disabled ||
	    (retry->flags & IW_RETRY_TYPE) != IW_RETRY_LIMIT)
		return -EINVAL;

	if (retry->flags & IW_RETRY_LONG) {
		wdev->wiphy->retry_long = retry->value;
		changed |= WIPHY_PARAM_RETRY_LONG;
	} else if (retry->flags & IW_RETRY_SHORT) {
		wdev->wiphy->retry_short = retry->value;
		changed |= WIPHY_PARAM_RETRY_SHORT;
	} else {
		wdev->wiphy->retry_short = retry->value;
		wdev->wiphy->retry_long = retry->value;
		changed |= WIPHY_PARAM_RETRY_LONG;
		changed |= WIPHY_PARAM_RETRY_SHORT;
	}

	if (!changed)
		return 0;

	err = rdev_set_wiphy_params(rdev, changed);
	if (err) {
		wdev->wiphy->retry_short = oshort;
		wdev->wiphy->retry_long = olong;
	}

	return err;
}