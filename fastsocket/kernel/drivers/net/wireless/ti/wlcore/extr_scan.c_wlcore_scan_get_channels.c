#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct conf_sched_scan_settings {scalar_t__ dwell_time_delta_per_probe_5; scalar_t__ dwell_time_delta_per_probe; scalar_t__ base_dwell_time; scalar_t__ num_probe_reqs; scalar_t__ max_dwell_time_delta; scalar_t__ dwell_time_passive; scalar_t__ dwell_time_dfs; } ;
struct conf_scan_settings {scalar_t__ min_dwell_time_active; scalar_t__ min_dwell_time_active_long; scalar_t__ max_dwell_time_active; scalar_t__ max_dwell_time_active_long; scalar_t__ dwell_time_passive; scalar_t__ dwell_time_dfs; } ;
struct TYPE_2__ {struct conf_sched_scan_settings sched_scan; struct conf_scan_settings scan; } ;
struct wl1271 {TYPE_1__ conf; } ;
struct ieee80211_channel {scalar_t__ flags; scalar_t__ band; int hw_value; scalar_t__ max_power; int /*<<< orphan*/  center_freq; } ;
struct conn_scan_ch_params {int channel; int /*<<< orphan*/  flags; scalar_t__ tx_power_att; void* max_duration; void* min_duration; void* passive_duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SCAN ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 scalar_t__ IEEE80211_CHAN_DISABLED ; 
 scalar_t__ IEEE80211_CHAN_PASSIVE_SCAN ; 
 scalar_t__ IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  SCAN_CHANNEL_FLAGS_DFS ; 
 int SCAN_TYPE_SEARCH ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wlcore_count_started_vifs (struct wl1271*) ; 

__attribute__((used)) static int
wlcore_scan_get_channels(struct wl1271 *wl,
			 struct ieee80211_channel *req_channels[],
			 u32 n_channels,
			 u32 n_ssids,
			 struct conn_scan_ch_params *channels,
			 u32 band, bool radar, bool passive,
			 int start, int max_channels,
			 u8 *n_pactive_ch,
			 int scan_type)
{
	int i, j;
	u32 flags;
	bool force_passive = !n_ssids;
	u32 min_dwell_time_active, max_dwell_time_active;
	u32 dwell_time_passive, dwell_time_dfs;

	/* configure dwell times according to scan type */
	if (scan_type == SCAN_TYPE_SEARCH) {
		struct conf_scan_settings *c = &wl->conf.scan;
		bool active_vif_exists = !!wlcore_count_started_vifs(wl);

		min_dwell_time_active = active_vif_exists ?
			c->min_dwell_time_active :
			c->min_dwell_time_active_long;
		max_dwell_time_active = active_vif_exists ?
			c->max_dwell_time_active :
			c->max_dwell_time_active_long;
		dwell_time_passive = c->dwell_time_passive;
		dwell_time_dfs = c->dwell_time_dfs;
	} else {
		struct conf_sched_scan_settings *c = &wl->conf.sched_scan;
		u32 delta_per_probe;

		if (band == IEEE80211_BAND_5GHZ)
			delta_per_probe = c->dwell_time_delta_per_probe_5;
		else
			delta_per_probe = c->dwell_time_delta_per_probe;

		min_dwell_time_active = c->base_dwell_time +
			 n_ssids * c->num_probe_reqs * delta_per_probe;

		max_dwell_time_active = min_dwell_time_active +
					c->max_dwell_time_delta;
		dwell_time_passive = c->dwell_time_passive;
		dwell_time_dfs = c->dwell_time_dfs;
	}
	min_dwell_time_active = DIV_ROUND_UP(min_dwell_time_active, 1000);
	max_dwell_time_active = DIV_ROUND_UP(max_dwell_time_active, 1000);
	dwell_time_passive = DIV_ROUND_UP(dwell_time_passive, 1000);
	dwell_time_dfs = DIV_ROUND_UP(dwell_time_dfs, 1000);

	for (i = 0, j = start;
	     i < n_channels && j < max_channels;
	     i++) {
		flags = req_channels[i]->flags;

		if (force_passive)
			flags |= IEEE80211_CHAN_PASSIVE_SCAN;

		if ((req_channels[i]->band == band) &&
		    !(flags & IEEE80211_CHAN_DISABLED) &&
		    (!!(flags & IEEE80211_CHAN_RADAR) == radar) &&
		    /* if radar is set, we ignore the passive flag */
		    (radar ||
		     !!(flags & IEEE80211_CHAN_PASSIVE_SCAN) == passive)) {
			wl1271_debug(DEBUG_SCAN, "band %d, center_freq %d ",
				     req_channels[i]->band,
				     req_channels[i]->center_freq);
			wl1271_debug(DEBUG_SCAN, "hw_value %d, flags %X",
				     req_channels[i]->hw_value,
				     req_channels[i]->flags);
			wl1271_debug(DEBUG_SCAN, "max_power %d",
				     req_channels[i]->max_power);
			wl1271_debug(DEBUG_SCAN, "min_dwell_time %d max dwell time %d",
				     min_dwell_time_active,
				     max_dwell_time_active);

			if (flags & IEEE80211_CHAN_RADAR) {
				channels[j].flags |= SCAN_CHANNEL_FLAGS_DFS;

				channels[j].passive_duration =
					cpu_to_le16(dwell_time_dfs);
			} else {
				channels[j].passive_duration =
					cpu_to_le16(dwell_time_passive);
			}

			channels[j].min_duration =
				cpu_to_le16(min_dwell_time_active);
			channels[j].max_duration =
				cpu_to_le16(max_dwell_time_active);

			channels[j].tx_power_att = req_channels[i]->max_power;
			channels[j].channel = req_channels[i]->hw_value;

			if (n_pactive_ch &&
			    (band == IEEE80211_BAND_2GHZ) &&
			    (channels[j].channel >= 12) &&
			    (channels[j].channel <= 14) &&
			    (flags & IEEE80211_CHAN_PASSIVE_SCAN) &&
			    !force_passive) {
				/* pactive channels treated as DFS */
				channels[j].flags = SCAN_CHANNEL_FLAGS_DFS;

				/*
				 * n_pactive_ch is counted down from the end of
				 * the passive channel list
				 */
				(*n_pactive_ch)++;
				wl1271_debug(DEBUG_SCAN, "n_pactive_ch = %d",
					     *n_pactive_ch);
			}

			j++;
		}
	}

	return j - start;
}