#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct b43_wldev {TYPE_4__* wl; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_8__ {TYPE_2__* hw; } ;
struct TYPE_7__ {struct ieee80211_channel* chan; } ;
struct TYPE_5__ {TYPE_3__ chandef; } ;
struct TYPE_6__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (TYPE_4__*) ; 
 int b43_phy_ht_set_channel (struct b43_wldev*,struct ieee80211_channel*,int) ; 
 int cfg80211_get_chandef_type (TYPE_3__*) ; 

__attribute__((used)) static int b43_phy_ht_op_switch_channel(struct b43_wldev *dev,
					unsigned int new_channel)
{
	struct ieee80211_channel *channel = dev->wl->hw->conf.chandef.chan;
	enum nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&dev->wl->hw->conf.chandef);

	if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		if ((new_channel < 1) || (new_channel > 14))
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	return b43_phy_ht_set_channel(dev, channel, channel_type);
}