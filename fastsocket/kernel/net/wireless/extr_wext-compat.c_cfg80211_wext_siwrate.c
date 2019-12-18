#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wireless_dev {TYPE_3__* wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ fixed; } ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int bitrate; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_bitrate_mask {TYPE_2__* control; } ;
typedef  int /*<<< orphan*/  mask ;
struct TYPE_6__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_5__ {int legacy; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_bitrate_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_NUM_BANDS ; 
 int /*<<< orphan*/  memset (struct cfg80211_bitrate_mask*,int /*<<< orphan*/ ,int) ; 
 int rdev_set_bitrate_mask (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *,struct cfg80211_bitrate_mask*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (TYPE_3__*) ; 

__attribute__((used)) static int cfg80211_wext_siwrate(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rate, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	struct cfg80211_bitrate_mask mask;
	u32 fixed, maxrate;
	struct ieee80211_supported_band *sband;
	int band, ridx;
	bool match = false;

	if (!rdev->ops->set_bitrate_mask)
		return -EOPNOTSUPP;

	memset(&mask, 0, sizeof(mask));
	fixed = 0;
	maxrate = (u32)-1;

	if (rate->value < 0) {
		/* nothing */
	} else if (rate->fixed) {
		fixed = rate->value / 100000;
	} else {
		maxrate = rate->value / 100000;
	}

	for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
		sband = wdev->wiphy->bands[band];
		if (sband == NULL)
			continue;
		for (ridx = 0; ridx < sband->n_bitrates; ridx++) {
			struct ieee80211_rate *srate = &sband->bitrates[ridx];
			if (fixed == srate->bitrate) {
				mask.control[band].legacy = 1 << ridx;
				match = true;
				break;
			}
			if (srate->bitrate <= maxrate) {
				mask.control[band].legacy |= 1 << ridx;
				match = true;
			}
		}
	}

	if (!match)
		return -EINVAL;

	return rdev_set_bitrate_mask(rdev, dev, NULL, &mask);
}