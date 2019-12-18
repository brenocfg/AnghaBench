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
struct wireless_dev {int /*<<< orphan*/  iftype; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;
typedef  enum cfg80211_chan_mode { ____Placeholder_cfg80211_chan_mode } cfg80211_chan_mode ;

/* Variables and functions */
 int cfg80211_can_use_iftype_chan (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ,struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
cfg80211_can_use_chan(struct cfg80211_registered_device *rdev,
		      struct wireless_dev *wdev,
		      struct ieee80211_channel *chan,
		      enum cfg80211_chan_mode chanmode)
{
	return cfg80211_can_use_iftype_chan(rdev, wdev, wdev->iftype,
					    chan, chanmode, 0);
}