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
struct TYPE_4__ {int default_key; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_2__ wext; scalar_t__ current_bss; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct key_params {char* key; int key_len; int /*<<< orphan*/  cipher; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int length; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_3__ {int /*<<< orphan*/  set_default_key; int /*<<< orphan*/  add_key; int /*<<< orphan*/  del_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WLAN_CIPHER_SUITE_WEP104 ; 
 int /*<<< orphan*/  WLAN_CIPHER_SUITE_WEP40 ; 
 int cfg80211_set_encryption (struct cfg80211_registered_device*,struct net_device*,int,int /*<<< orphan*/ *,int,int,int,struct key_params*) ; 
 int /*<<< orphan*/  memset (struct key_params*,int /*<<< orphan*/ ,int) ; 
 int rdev_set_default_key (struct cfg80211_registered_device*,struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_siwencode(struct net_device *dev,
				   struct iw_request_info *info,
				   struct iw_point *erq, char *keybuf)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	int idx, err;
	bool remove = false;
	struct key_params params;

	if (wdev->iftype != NL80211_IFTYPE_STATION &&
	    wdev->iftype != NL80211_IFTYPE_ADHOC)
		return -EOPNOTSUPP;

	/* no use -- only MFP (set_default_mgmt_key) is optional */
	if (!rdev->ops->del_key ||
	    !rdev->ops->add_key ||
	    !rdev->ops->set_default_key)
		return -EOPNOTSUPP;

	idx = erq->flags & IW_ENCODE_INDEX;
	if (idx == 0) {
		idx = wdev->wext.default_key;
		if (idx < 0)
			idx = 0;
	} else if (idx < 1 || idx > 4)
		return -EINVAL;
	else
		idx--;

	if (erq->flags & IW_ENCODE_DISABLED)
		remove = true;
	else if (erq->length == 0) {
		/* No key data - just set the default TX key index */
		err = 0;
		wdev_lock(wdev);
		if (wdev->current_bss)
			err = rdev_set_default_key(rdev, dev, idx, true,
						   true);
		if (!err)
			wdev->wext.default_key = idx;
		wdev_unlock(wdev);
		return err;
	}

	memset(&params, 0, sizeof(params));
	params.key = keybuf;
	params.key_len = erq->length;
	if (erq->length == 5)
		params.cipher = WLAN_CIPHER_SUITE_WEP40;
	else if (erq->length == 13)
		params.cipher = WLAN_CIPHER_SUITE_WEP104;
	else if (!remove)
		return -EINVAL;

	return cfg80211_set_encryption(rdev, dev, false, NULL, remove,
				       wdev->wext.default_key == -1,
				       idx, &params);
}