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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;
struct iw_mlme {int cmd; int /*<<< orphan*/  reason_code; TYPE_1__ addr; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int __cfg80211_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

int cfg80211_wext_siwmlme(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *data, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct iw_mlme *mlme = (struct iw_mlme *)extra;
	struct cfg80211_registered_device *rdev;
	int err;

	if (!wdev)
		return -EOPNOTSUPP;

	rdev = wiphy_to_dev(wdev->wiphy);

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EINVAL;

	if (mlme->addr.sa_family != ARPHRD_ETHER)
		return -EINVAL;

	wdev_lock(wdev);
	switch (mlme->cmd) {
	case IW_MLME_DEAUTH:
	case IW_MLME_DISASSOC:
		err = __cfg80211_disconnect(rdev, dev, mlme->reason_code,
					    true);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}
	wdev_unlock(wdev);

	return err;
}