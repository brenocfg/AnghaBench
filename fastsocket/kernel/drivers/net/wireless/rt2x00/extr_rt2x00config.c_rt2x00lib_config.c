#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_12__ {int /*<<< orphan*/  channel; } ;
struct rt2x00lib_conf {TYPE_6__ rf; TYPE_6__ channel; struct ieee80211_conf* conf; } ;
struct TYPE_7__ {int /*<<< orphan*/ * channels_info; int /*<<< orphan*/ * channels; } ;
struct rt2x00_dev {int /*<<< orphan*/  long_retry; int /*<<< orphan*/  short_retry; int /*<<< orphan*/  tx_power; int /*<<< orphan*/  curr_freq; int /*<<< orphan*/  curr_band; int /*<<< orphan*/  flags; int /*<<< orphan*/  autowakeup_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  beacon_int; scalar_t__ last_beacon; int /*<<< orphan*/  cap_flags; TYPE_3__* ops; int /*<<< orphan*/  rf_channel; TYPE_1__ spec; } ;
struct TYPE_11__ {TYPE_4__* chan; } ;
struct ieee80211_conf {int flags; size_t max_sleep_period; int /*<<< orphan*/  long_frame_max_tx_count; int /*<<< orphan*/  short_frame_max_tx_count; int /*<<< orphan*/  power_level; TYPE_5__ chandef; } ;
typedef  int /*<<< orphan*/  libconf ;
struct TYPE_10__ {size_t hw_value; int /*<<< orphan*/  center_freq; int /*<<< orphan*/  band; } ;
struct TYPE_9__ {TYPE_2__* lib; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* config ) (struct rt2x00_dev*,struct rt2x00lib_conf*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHANNEL_HT40 ; 
 int /*<<< orphan*/  CONFIG_HT_DISABLED ; 
 int /*<<< orphan*/  CONFIG_POWERSAVING ; 
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 unsigned int IEEE80211_CONF_CHANGE_CHANNEL ; 
 unsigned int IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  REQUIRE_PS_AUTOWAKE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_is_ht (struct ieee80211_conf*) ; 
 scalar_t__ conf_is_ht40 (struct ieee80211_conf*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct rt2x00lib_conf*,int /*<<< orphan*/ ,int) ; 
 size_t msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t rt2x00ht_center_channel (struct rt2x00_dev*,struct ieee80211_conf*) ; 
 int /*<<< orphan*/  rt2x00link_reset_tuner (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct rt2x00lib_conf*,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_config(struct rt2x00_dev *rt2x00dev,
		      struct ieee80211_conf *conf,
		      unsigned int ieee80211_flags)
{
	struct rt2x00lib_conf libconf;
	u16 hw_value;
	u16 autowake_timeout;
	u16 beacon_int;
	u16 beacon_diff;

	memset(&libconf, 0, sizeof(libconf));

	libconf.conf = conf;

	if (ieee80211_flags & IEEE80211_CONF_CHANGE_CHANNEL) {
		if (!conf_is_ht(conf))
			set_bit(CONFIG_HT_DISABLED, &rt2x00dev->flags);
		else
			clear_bit(CONFIG_HT_DISABLED, &rt2x00dev->flags);

		if (conf_is_ht40(conf)) {
			set_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags);
			hw_value = rt2x00ht_center_channel(rt2x00dev, conf);
		} else {
			clear_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags);
			hw_value = conf->chandef.chan->hw_value;
		}

		memcpy(&libconf.rf,
		       &rt2x00dev->spec.channels[hw_value],
		       sizeof(libconf.rf));

		memcpy(&libconf.channel,
		       &rt2x00dev->spec.channels_info[hw_value],
		       sizeof(libconf.channel));

		/* Used for VCO periodic calibration */
		rt2x00dev->rf_channel = libconf.rf.channel;
	}

	if (test_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags) &&
	    (ieee80211_flags & IEEE80211_CONF_CHANGE_PS))
		cancel_delayed_work_sync(&rt2x00dev->autowakeup_work);

	/*
	 * Start configuration.
	 */
	rt2x00dev->ops->lib->config(rt2x00dev, &libconf, ieee80211_flags);

	/*
	 * Some configuration changes affect the link quality
	 * which means we need to reset the link tuner.
	 */
	if (ieee80211_flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt2x00link_reset_tuner(rt2x00dev, false);

	if (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    test_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags) &&
	    (ieee80211_flags & IEEE80211_CONF_CHANGE_PS) &&
	    (conf->flags & IEEE80211_CONF_PS)) {
		beacon_diff = (long)jiffies - (long)rt2x00dev->last_beacon;
		beacon_int = msecs_to_jiffies(rt2x00dev->beacon_int);

		if (beacon_diff > beacon_int)
			beacon_diff = 0;

		autowake_timeout = (conf->max_sleep_period * beacon_int) - beacon_diff;
		queue_delayed_work(rt2x00dev->workqueue,
				   &rt2x00dev->autowakeup_work,
				   autowake_timeout - 15);
	}

	if (conf->flags & IEEE80211_CONF_PS)
		set_bit(CONFIG_POWERSAVING, &rt2x00dev->flags);
	else
		clear_bit(CONFIG_POWERSAVING, &rt2x00dev->flags);

	rt2x00dev->curr_band = conf->chandef.chan->band;
	rt2x00dev->curr_freq = conf->chandef.chan->center_freq;
	rt2x00dev->tx_power = conf->power_level;
	rt2x00dev->short_retry = conf->short_frame_max_tx_count;
	rt2x00dev->long_retry = conf->long_frame_max_tx_count;
}