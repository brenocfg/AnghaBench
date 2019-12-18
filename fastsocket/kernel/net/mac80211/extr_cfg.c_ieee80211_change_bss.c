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
typedef  scalar_t__ u16 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct net_device {int dummy; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_3__* bitrates; } ;
struct TYPE_10__ {int oppps_ctwindow; } ;
struct TYPE_11__ {scalar_t__ use_cts_prot; scalar_t__ use_short_preamble; int use_short_slot; TYPE_4__ p2p_noa_attr; scalar_t__ ht_operation_mode; int /*<<< orphan*/  basic_rates; } ;
struct TYPE_12__ {TYPE_5__ bss_conf; } ;
struct TYPE_7__ {int /*<<< orphan*/  beacon; } ;
struct TYPE_8__ {TYPE_1__ ap; } ;
struct ieee80211_sub_if_data {TYPE_6__ vif; int /*<<< orphan*/  flags; TYPE_2__ u; } ;
struct bss_parameters {scalar_t__ use_cts_prot; scalar_t__ use_short_preamble; int use_short_slot_time; int* basic_rates; int basic_rates_len; scalar_t__ ap_isolate; scalar_t__ ht_opmode; int p2p_ctwindow; scalar_t__ p2p_opp_ps; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_9__ {int bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  BSS_CHANGED_BASIC_RATES ; 
 int /*<<< orphan*/  BSS_CHANGED_ERP_CTS_PROT ; 
 int /*<<< orphan*/  BSS_CHANGED_ERP_PREAMBLE ; 
 int /*<<< orphan*/  BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  BSS_CHANGED_HT ; 
 int /*<<< orphan*/  BSS_CHANGED_P2P_PS ; 
 int ENOENT ; 
 int IEEE80211_BAND_5GHZ ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_P2P_OPPPS_CTWINDOW_MASK ; 
 int IEEE80211_P2P_OPPPS_ENABLE_BIT ; 
 int /*<<< orphan*/  IEEE80211_SDATA_DONT_BRIDGE_PACKETS ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_get_sdata_band (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_change_bss(struct wiphy *wiphy,
				struct net_device *dev,
				struct bss_parameters *params)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	enum ieee80211_band band;
	u32 changed = 0;

	if (!rtnl_dereference(sdata->u.ap.beacon))
		return -ENOENT;

	band = ieee80211_get_sdata_band(sdata);

	if (params->use_cts_prot >= 0) {
		sdata->vif.bss_conf.use_cts_prot = params->use_cts_prot;
		changed |= BSS_CHANGED_ERP_CTS_PROT;
	}
	if (params->use_short_preamble >= 0) {
		sdata->vif.bss_conf.use_short_preamble =
			params->use_short_preamble;
		changed |= BSS_CHANGED_ERP_PREAMBLE;
	}

	if (!sdata->vif.bss_conf.use_short_slot &&
	    band == IEEE80211_BAND_5GHZ) {
		sdata->vif.bss_conf.use_short_slot = true;
		changed |= BSS_CHANGED_ERP_SLOT;
	}

	if (params->use_short_slot_time >= 0) {
		sdata->vif.bss_conf.use_short_slot =
			params->use_short_slot_time;
		changed |= BSS_CHANGED_ERP_SLOT;
	}

	if (params->basic_rates) {
		int i, j;
		u32 rates = 0;
		struct ieee80211_supported_band *sband = wiphy->bands[band];

		for (i = 0; i < params->basic_rates_len; i++) {
			int rate = (params->basic_rates[i] & 0x7f) * 5;
			for (j = 0; j < sband->n_bitrates; j++) {
				if (sband->bitrates[j].bitrate == rate)
					rates |= BIT(j);
			}
		}
		sdata->vif.bss_conf.basic_rates = rates;
		changed |= BSS_CHANGED_BASIC_RATES;
	}

	if (params->ap_isolate >= 0) {
		if (params->ap_isolate)
			sdata->flags |= IEEE80211_SDATA_DONT_BRIDGE_PACKETS;
		else
			sdata->flags &= ~IEEE80211_SDATA_DONT_BRIDGE_PACKETS;
	}

	if (params->ht_opmode >= 0) {
		sdata->vif.bss_conf.ht_operation_mode =
			(u16) params->ht_opmode;
		changed |= BSS_CHANGED_HT;
	}

	if (params->p2p_ctwindow >= 0) {
		sdata->vif.bss_conf.p2p_noa_attr.oppps_ctwindow &=
					~IEEE80211_P2P_OPPPS_CTWINDOW_MASK;
		sdata->vif.bss_conf.p2p_noa_attr.oppps_ctwindow |=
			params->p2p_ctwindow & IEEE80211_P2P_OPPPS_CTWINDOW_MASK;
		changed |= BSS_CHANGED_P2P_PS;
	}

	if (params->p2p_opp_ps > 0) {
		sdata->vif.bss_conf.p2p_noa_attr.oppps_ctwindow |=
					IEEE80211_P2P_OPPPS_ENABLE_BIT;
		changed |= BSS_CHANGED_P2P_PS;
	} else if (params->p2p_opp_ps == 0) {
		sdata->vif.bss_conf.p2p_noa_attr.oppps_ctwindow &=
					~IEEE80211_P2P_OPPPS_ENABLE_BIT;
		changed |= BSS_CHANGED_P2P_PS;
	}

	ieee80211_bss_info_change_notify(sdata, changed);

	return 0;
}