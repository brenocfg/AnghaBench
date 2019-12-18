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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_9__ {TYPE_6__* chan; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_11__ {TYPE_4__ conf; } ;
struct ieee80211_local {int /*<<< orphan*/  next_scan_state; TYPE_5__ hw; TYPE_2__* scan_req; int /*<<< orphan*/  mtx; int /*<<< orphan*/  scan_sdata; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_12__ {int band; } ;
struct TYPE_8__ {int n_ssids; int /*<<< orphan*/ * rates; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; TYPE_1__* ssids; scalar_t__ no_cck; } ;
struct TYPE_7__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 unsigned long IEEE80211_CHANNEL_TIME ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_NO_CCK_RATE ; 
 int /*<<< orphan*/  IEEE80211_TX_INTFL_OFFCHAN_TX_OK ; 
 int /*<<< orphan*/  SCAN_DECISION ; 
 int /*<<< orphan*/  ieee80211_send_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_scan_state_send_probe(struct ieee80211_local *local,
					    unsigned long *next_delay)
{
	int i;
	struct ieee80211_sub_if_data *sdata;
	enum ieee80211_band band = local->hw.conf.chandef.chan->band;
	u32 tx_flags;

	tx_flags = IEEE80211_TX_INTFL_OFFCHAN_TX_OK;
	if (local->scan_req->no_cck)
		tx_flags |= IEEE80211_TX_CTL_NO_CCK_RATE;

	sdata = rcu_dereference_protected(local->scan_sdata,
					  lockdep_is_held(&local->mtx));

	for (i = 0; i < local->scan_req->n_ssids; i++)
		ieee80211_send_probe_req(
			sdata, NULL,
			local->scan_req->ssids[i].ssid,
			local->scan_req->ssids[i].ssid_len,
			local->scan_req->ie, local->scan_req->ie_len,
			local->scan_req->rates[band], false,
			tx_flags, local->hw.conf.chandef.chan, true);

	/*
	 * After sending probe requests, wait for probe responses
	 * on the channel.
	 */
	*next_delay = IEEE80211_CHANNEL_TIME;
	local->next_scan_state = SCAN_DECISION;
}