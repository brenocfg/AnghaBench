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
struct cfg80211_registered_device {int /*<<< orphan*/  dfs_update_channels_wk; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DFS_MIN_NOP_TIME_MS ; 
 int /*<<< orphan*/  NL80211_DFS_UNAVAILABLE ; 
 int /*<<< orphan*/  NL80211_RADAR_DETECTED ; 
 int /*<<< orphan*/  cfg80211_set_dfs_state (struct wiphy*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_radar_notify (struct cfg80211_registered_device*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_cfg80211_radar_event (struct wiphy*,struct cfg80211_chan_def*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

void cfg80211_radar_event(struct wiphy *wiphy,
			  struct cfg80211_chan_def *chandef,
			  gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);
	unsigned long timeout;

	trace_cfg80211_radar_event(wiphy, chandef);

	/* only set the chandef supplied channel to unavailable, in
	 * case the radar is detected on only one of multiple channels
	 * spanned by the chandef.
	 */
	cfg80211_set_dfs_state(wiphy, chandef, NL80211_DFS_UNAVAILABLE);

	timeout = msecs_to_jiffies(IEEE80211_DFS_MIN_NOP_TIME_MS);
	queue_delayed_work(cfg80211_wq, &rdev->dfs_update_channels_wk,
			   timeout);

	nl80211_radar_notify(rdev, chandef, NL80211_RADAR_DETECTED, NULL, gfp);
}