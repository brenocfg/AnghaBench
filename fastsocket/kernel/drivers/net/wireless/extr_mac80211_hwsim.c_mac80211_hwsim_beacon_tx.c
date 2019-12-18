#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct mac80211_hwsim_data {scalar_t__ tsf_offset; scalar_t__ abs_bcn_ts; struct ieee80211_hw* hw; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  chanctx_conf; } ;
struct TYPE_6__ {int /*<<< orphan*/  rates; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_rate {int bitrate; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {TYPE_2__ beacon; } ;
struct ieee80211_mgmt {TYPE_3__ u; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  chan; } ;
struct TYPE_10__ {TYPE_4__ def; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  hwsim_check_magic (struct ieee80211_vif*) ; 
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (struct ieee80211_hw*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_get_tx_rates (struct ieee80211_vif*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mac80211_hwsim_get_tsf_raw () ; 
 int /*<<< orphan*/  mac80211_hwsim_tx_frame (struct ieee80211_hw*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ rctbl ; 
 TYPE_5__* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac80211_hwsim_beacon_tx(void *arg, u8 *mac,
				     struct ieee80211_vif *vif)
{
	struct mac80211_hwsim_data *data = arg;
	struct ieee80211_hw *hw = data->hw;
	struct ieee80211_tx_info *info;
	struct ieee80211_rate *txrate;
	struct ieee80211_mgmt *mgmt;
	struct sk_buff *skb;

	hwsim_check_magic(vif);

	if (vif->type != NL80211_IFTYPE_AP &&
	    vif->type != NL80211_IFTYPE_MESH_POINT &&
	    vif->type != NL80211_IFTYPE_ADHOC)
		return;

	skb = ieee80211_beacon_get(hw, vif);
	if (skb == NULL)
		return;
	info = IEEE80211_SKB_CB(skb);
	if (rctbl)
		ieee80211_get_tx_rates(vif, NULL, skb,
				       info->control.rates,
				       ARRAY_SIZE(info->control.rates));

	txrate = ieee80211_get_tx_rate(hw, info);

	mgmt = (struct ieee80211_mgmt *) skb->data;
	/* fake header transmission time */
	data->abs_bcn_ts = mac80211_hwsim_get_tsf_raw();
	mgmt->u.beacon.timestamp = cpu_to_le64(data->abs_bcn_ts +
					       data->tsf_offset +
					       24 * 8 * 10 / txrate->bitrate);

	mac80211_hwsim_tx_frame(hw, skb,
				rcu_dereference(vif->chanctx_conf)->def.chan);
}