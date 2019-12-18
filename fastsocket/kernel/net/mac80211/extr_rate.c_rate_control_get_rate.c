#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sta {int dummy; } ;
struct sta_info {void* rate_ctrl_priv; struct ieee80211_sta sta; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct ieee80211_tx_rate_control {int /*<<< orphan*/  skb; } ;
struct TYPE_10__ {TYPE_5__* rates; } ;
struct ieee80211_tx_info {TYPE_4__ control; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; TYPE_3__* local; } ;
struct TYPE_11__ {int idx; scalar_t__ count; scalar_t__ flags; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {TYPE_2__ hw; struct rate_control_ref* rate_ctrl; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_rate ) (int /*<<< orphan*/ ,struct ieee80211_sta*,void*,struct ieee80211_tx_rate_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_5__*) ; 
 int IEEE80211_HW_HAS_RATE_CONTROL ; 
 int IEEE80211_HW_SUPPORTS_RC_TABLE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int IEEE80211_TX_MAX_RATES ; 
 int /*<<< orphan*/  WLAN_STA_RATE_CONTROL ; 
 int /*<<< orphan*/  ieee80211_get_tx_rates (int /*<<< orphan*/ *,struct ieee80211_sta*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_sta*,void*,struct ieee80211_tx_rate_control*) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

void rate_control_get_rate(struct ieee80211_sub_if_data *sdata,
			   struct sta_info *sta,
			   struct ieee80211_tx_rate_control *txrc)
{
	struct rate_control_ref *ref = sdata->local->rate_ctrl;
	void *priv_sta = NULL;
	struct ieee80211_sta *ista = NULL;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	int i;

	if (sta && test_sta_flag(sta, WLAN_STA_RATE_CONTROL)) {
		ista = &sta->sta;
		priv_sta = sta->rate_ctrl_priv;
	}

	for (i = 0; i < IEEE80211_TX_MAX_RATES; i++) {
		info->control.rates[i].idx = -1;
		info->control.rates[i].flags = 0;
		info->control.rates[i].count = 0;
	}

	if (sdata->local->hw.flags & IEEE80211_HW_HAS_RATE_CONTROL)
		return;

	ref->ops->get_rate(ref->priv, ista, priv_sta, txrc);

	if (sdata->local->hw.flags & IEEE80211_HW_SUPPORTS_RC_TABLE)
		return;

	ieee80211_get_tx_rates(&sdata->vif, ista, txrc->skb,
			       info->control.rates,
			       ARRAY_SIZE(info->control.rates));
}