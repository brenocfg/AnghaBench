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
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_IBSS ; 
 int IEEE80211_CHAN_PASSIVE_SCAN ; 
 int IEEE80211_CHAN_RADAR ; 
 int cfg80211_chandef_usable (struct wiphy*,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  trace_cfg80211_reg_can_beacon (struct wiphy*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  trace_cfg80211_return_bool (int) ; 

bool cfg80211_reg_can_beacon(struct wiphy *wiphy,
			     struct cfg80211_chan_def *chandef)
{
	bool res;

	trace_cfg80211_reg_can_beacon(wiphy, chandef);

	res = cfg80211_chandef_usable(wiphy, chandef,
				      IEEE80211_CHAN_DISABLED |
				      IEEE80211_CHAN_PASSIVE_SCAN |
				      IEEE80211_CHAN_NO_IBSS |
				      IEEE80211_CHAN_RADAR);

	trace_cfg80211_return_bool(res);
	return res;
}