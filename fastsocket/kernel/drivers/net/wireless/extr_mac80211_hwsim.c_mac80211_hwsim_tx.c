#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct mac80211_hwsim_data {struct ieee80211_channel* tmp_chan; scalar_t__ idle; struct ieee80211_channel* channel; } ;
struct TYPE_8__ {TYPE_4__* rates; TYPE_3__* vif; } ;
struct ieee80211_tx_info {int hw_queue; int flags; TYPE_2__ control; struct ieee80211_channel** rate_driver_data; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mac80211_hwsim_data* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_7__ {struct ieee80211_channel* chan; } ;
struct ieee80211_chanctx_conf {TYPE_1__ def; } ;
struct TYPE_10__ {int count; int idx; } ;
struct TYPE_9__ {int /*<<< orphan*/  chanctx_conf; } ;

/* Variables and functions */
 scalar_t__ ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_4__*) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 scalar_t__ WARN (int,char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int channels ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  hwsim_check_magic (TYPE_3__*) ; 
 int /*<<< orphan*/  hwsim_check_sta_magic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_tx_rates (TYPE_3__*,int /*<<< orphan*/ ,struct sk_buff*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  mac80211_hwsim_monitor_ack (struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac80211_hwsim_monitor_rx (struct ieee80211_hw*,struct sk_buff*,struct ieee80211_channel*) ; 
 void mac80211_hwsim_tx_frame_nl (struct ieee80211_hw*,struct sk_buff*,scalar_t__) ; 
 int mac80211_hwsim_tx_frame_no_nl (struct ieee80211_hw*,struct sk_buff*,struct ieee80211_channel*) ; 
 scalar_t__ rctbl ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wmediumd_portid ; 

__attribute__((used)) static void mac80211_hwsim_tx(struct ieee80211_hw *hw,
			      struct ieee80211_tx_control *control,
			      struct sk_buff *skb)
{
	struct mac80211_hwsim_data *data = hw->priv;
	struct ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *channel;
	bool ack;
	u32 _portid;

	if (WARN_ON(skb->len < 10)) {
		/* Should not happen; just a sanity check for addr1 use */
		dev_kfree_skb(skb);
		return;
	}

	if (channels == 1) {
		channel = data->channel;
	} else if (txi->hw_queue == 4) {
		channel = data->tmp_chan;
	} else {
		chanctx_conf = rcu_dereference(txi->control.vif->chanctx_conf);
		if (chanctx_conf)
			channel = chanctx_conf->def.chan;
		else
			channel = NULL;
	}

	if (WARN(!channel, "TX w/o channel - queue = %d\n", txi->hw_queue)) {
		dev_kfree_skb(skb);
		return;
	}

	if (data->idle && !data->tmp_chan) {
		wiphy_debug(hw->wiphy, "Trying to TX when idle - reject\n");
		dev_kfree_skb(skb);
		return;
	}

	if (txi->control.vif)
		hwsim_check_magic(txi->control.vif);
	if (control->sta)
		hwsim_check_sta_magic(control->sta);

	if (rctbl)
		ieee80211_get_tx_rates(txi->control.vif, control->sta, skb,
				       txi->control.rates,
				       ARRAY_SIZE(txi->control.rates));

	txi->rate_driver_data[0] = channel;
	mac80211_hwsim_monitor_rx(hw, skb, channel);

	/* wmediumd mode check */
	_portid = ACCESS_ONCE(wmediumd_portid);

	if (_portid)
		return mac80211_hwsim_tx_frame_nl(hw, skb, _portid);

	/* NO wmediumd detected, perfect medium simulation */
	ack = mac80211_hwsim_tx_frame_no_nl(hw, skb, channel);

	if (ack && skb->len >= 16) {
		struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
		mac80211_hwsim_monitor_ack(channel, hdr->addr2);
	}

	ieee80211_tx_info_clear_status(txi);

	/* frame was transmitted at most favorable rate at first attempt */
	txi->control.rates[0].count = 1;
	txi->control.rates[1].idx = -1;

	if (!(txi->flags & IEEE80211_TX_CTL_NO_ACK) && ack)
		txi->flags |= IEEE80211_TX_STAT_ACK;
	ieee80211_tx_status_irqsafe(hw, skb);
}