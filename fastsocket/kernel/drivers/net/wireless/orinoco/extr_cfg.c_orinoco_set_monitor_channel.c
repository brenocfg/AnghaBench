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
struct wiphy {int dummy; } ;
struct hermes {TYPE_2__* ops; } ;
struct orinoco_private {int channel_mask; int channel; scalar_t__ iw_mode; struct hermes hw; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_4__ {int (* cmd_wait ) (struct hermes*,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {scalar_t__ band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int HERMES_CMD_TEST ; 
 int HERMES_TEST_SET_CHANNEL ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ NL80211_CHAN_NO_HT ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int NUM_CHANNELS ; 
 scalar_t__ cfg80211_get_chandef_type (struct cfg80211_chan_def*) ; 
 int ieee80211_freq_to_dsss_chan (int /*<<< orphan*/ ) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 
 int stub1 (struct hermes*,int,int,int /*<<< orphan*/ *) ; 
 struct orinoco_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int orinoco_set_monitor_channel(struct wiphy *wiphy,
				       struct cfg80211_chan_def *chandef)
{
	struct orinoco_private *priv = wiphy_priv(wiphy);
	int err = 0;
	unsigned long flags;
	int channel;

	if (!chandef->chan)
		return -EINVAL;

	if (cfg80211_get_chandef_type(chandef) != NL80211_CHAN_NO_HT)
		return -EINVAL;

	if (chandef->chan->band != IEEE80211_BAND_2GHZ)
		return -EINVAL;

	channel = ieee80211_freq_to_dsss_chan(chandef->chan->center_freq);

	if ((channel < 1) || (channel > NUM_CHANNELS) ||
	     !(priv->channel_mask & (1 << (channel - 1))))
		return -EINVAL;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	priv->channel = channel;
	if (priv->iw_mode == NL80211_IFTYPE_MONITOR) {
		/* Fast channel change - no commit if successful */
		struct hermes *hw = &priv->hw;
		err = hw->ops->cmd_wait(hw, HERMES_CMD_TEST |
					    HERMES_TEST_SET_CHANNEL,
					channel, NULL);
	}
	orinoco_unlock(priv, &flags);

	return err;
}