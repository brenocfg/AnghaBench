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
typedef  char u8 ;
struct TYPE_2__ {int ie_len; char* ie; } ;
struct wireless_dev {scalar_t__ iftype; scalar_t__ sme_state; TYPE_1__ wext; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG80211_SME_IDLE ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int __cfg80211_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

int cfg80211_wext_siwgenie(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_point *data, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	u8 *ie = extra;
	int ie_len = data->length, err;

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	if (!ie_len)
		ie = NULL;

	wdev_lock(wdev);

	/* no change */
	err = 0;
	if (wdev->wext.ie_len == ie_len &&
	    memcmp(wdev->wext.ie, ie, ie_len) == 0)
		goto out;

	if (ie_len) {
		ie = kmemdup(extra, ie_len, GFP_KERNEL);
		if (!ie) {
			err = -ENOMEM;
			goto out;
		}
	} else
		ie = NULL;

	kfree(wdev->wext.ie);
	wdev->wext.ie = ie;
	wdev->wext.ie_len = ie_len;

	if (wdev->sme_state != CFG80211_SME_IDLE) {
		err = __cfg80211_disconnect(rdev, dev,
					    WLAN_REASON_DEAUTH_LEAVING, false);
		if (err)
			goto out;
	}

	/* userspace better not think we'll reconnect */
	err = 0;
 out:
	wdev_unlock(wdev);
	return err;
}