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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_channel {int /*<<< orphan*/  band; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* ieee80211_build_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ieee80211_channel*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_skb_tid_band (struct ieee80211_sub_if_data*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 

void ieee80211_send_probe_req(struct ieee80211_sub_if_data *sdata, u8 *dst,
			      const u8 *ssid, size_t ssid_len,
			      const u8 *ie, size_t ie_len,
			      u32 ratemask, bool directed, u32 tx_flags,
			      struct ieee80211_channel *channel, bool scan)
{
	struct sk_buff *skb;

	skb = ieee80211_build_probe_req(sdata, dst, ratemask, channel,
					ssid, ssid_len,
					ie, ie_len, directed);
	if (skb) {
		IEEE80211_SKB_CB(skb)->flags |= tx_flags;
		if (scan)
			ieee80211_tx_skb_tid_band(sdata, skb, 7, channel->band);
		else
			ieee80211_tx_skb(sdata, skb);
	}
}