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
struct cfg80211_chan_def {int /*<<< orphan*/  center_freq2; int /*<<< orphan*/  center_freq1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int cfg80211_chandef_get_width (struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def const*) ; 
 int cfg80211_get_chans_dfs_required (struct wiphy*,int /*<<< orphan*/ ,int) ; 

int cfg80211_chandef_dfs_required(struct wiphy *wiphy,
				  const struct cfg80211_chan_def *chandef)
{
	int width;
	int r;

	if (WARN_ON(!cfg80211_chandef_valid(chandef)))
		return -EINVAL;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		return -EINVAL;

	r = cfg80211_get_chans_dfs_required(wiphy, chandef->center_freq1,
					    width);
	if (r)
		return r;

	if (!chandef->center_freq2)
		return 0;

	return cfg80211_get_chans_dfs_required(wiphy, chandef->center_freq2,
					       width);
}