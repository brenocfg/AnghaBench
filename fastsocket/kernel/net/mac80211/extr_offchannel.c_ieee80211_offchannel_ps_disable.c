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
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_4__ {scalar_t__ dynamic_ps_timeout; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__ conf; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  dynamic_ps_timer; scalar_t__ offchannel_ps_enabled; int /*<<< orphan*/  ps_sdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int /*<<< orphan*/  IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_nullfunc (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_beacon_monitor (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_conn_monitor (struct ieee80211_sub_if_data*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void ieee80211_offchannel_ps_disable(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;

	if (!local->ps_sdata)
		ieee80211_send_nullfunc(local, sdata, 0);
	else if (local->offchannel_ps_enabled) {
		/*
		 * In !IEEE80211_HW_PS_NULLFUNC_STACK case the hardware
		 * will send a nullfunc frame with the powersave bit set
		 * even though the AP already knows that we are sleeping.
		 * This could be avoided by sending a null frame with power
		 * save bit disabled before enabling the power save, but
		 * this doesn't gain anything.
		 *
		 * When IEEE80211_HW_PS_NULLFUNC_STACK is enabled, no need
		 * to send a nullfunc frame because AP already knows that
		 * we are sleeping, let's just enable power save mode in
		 * hardware.
		 */
		/* TODO:  Only set hardware if CONF_PS changed?
		 * TODO:  Should we set offchannel_ps_enabled to false?
		 */
		local->hw.conf.flags |= IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	} else if (local->hw.conf.dynamic_ps_timeout > 0) {
		/*
		 * If IEEE80211_CONF_PS was not set and the dynamic_ps_timer
		 * had been running before leaving the operating channel,
		 * restart the timer now and send a nullfunc frame to inform
		 * the AP that we are awake.
		 */
		ieee80211_send_nullfunc(local, sdata, 0);
		mod_timer(&local->dynamic_ps_timer, jiffies +
			  msecs_to_jiffies(local->hw.conf.dynamic_ps_timeout));
	}

	ieee80211_sta_reset_beacon_monitor(sdata);
	ieee80211_sta_reset_conn_monitor(sdata);
}