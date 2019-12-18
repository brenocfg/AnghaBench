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
typedef  int /*<<< orphan*/  vifparams ;
typedef  int u32 ;
struct wireless_dev {int iftype; int /*<<< orphan*/  wiphy; } ;
struct vif_params {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EINVAL ; 
#define  IW_MODE_ADHOC 131 
#define  IW_MODE_INFRA 130 
#define  IW_MODE_MONITOR 129 
#define  IW_MODE_REPEAT 128 
 int NL80211_IFTYPE_ADHOC ; 
 int NL80211_IFTYPE_MONITOR ; 
 int NL80211_IFTYPE_STATION ; 
 int NL80211_IFTYPE_WDS ; 
 int cfg80211_change_iface (struct cfg80211_registered_device*,struct net_device*,int,int /*<<< orphan*/ *,struct vif_params*) ; 
 int /*<<< orphan*/  cfg80211_lock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  memset (struct vif_params*,int /*<<< orphan*/ ,int) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

int cfg80211_wext_siwmode(struct net_device *dev, struct iw_request_info *info,
			  u32 *mode, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev;
	struct vif_params vifparams;
	enum nl80211_iftype type;
	int ret;

	rdev = wiphy_to_dev(wdev->wiphy);

	switch (*mode) {
	case IW_MODE_INFRA:
		type = NL80211_IFTYPE_STATION;
		break;
	case IW_MODE_ADHOC:
		type = NL80211_IFTYPE_ADHOC;
		break;
	case IW_MODE_REPEAT:
		type = NL80211_IFTYPE_WDS;
		break;
	case IW_MODE_MONITOR:
		type = NL80211_IFTYPE_MONITOR;
		break;
	default:
		return -EINVAL;
	}

	if (type == wdev->iftype)
		return 0;

	memset(&vifparams, 0, sizeof(vifparams));

	cfg80211_lock_rdev(rdev);
	ret = cfg80211_change_iface(rdev, dev, type, NULL, &vifparams);
	cfg80211_unlock_rdev(rdev);

	return ret;
}