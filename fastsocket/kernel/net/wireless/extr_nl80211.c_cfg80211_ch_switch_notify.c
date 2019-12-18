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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  channel; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  nl80211_ch_switch_notify (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_ch_switch_notify (struct net_device*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

void cfg80211_ch_switch_notify(struct net_device *dev,
			       struct cfg80211_chan_def *chandef)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);

	trace_cfg80211_ch_switch_notify(dev, chandef);

	wdev_lock(wdev);

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_AP &&
		    wdev->iftype != NL80211_IFTYPE_P2P_GO))
		goto out;

	wdev->channel = chandef->chan;
	nl80211_ch_switch_notify(rdev, dev, chandef, GFP_KERNEL);
out:
	wdev_unlock(wdev);
	return;
}