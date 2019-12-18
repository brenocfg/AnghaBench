#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int priority; int /*<<< orphan*/  dev; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_xmit (struct ieee80211_sub_if_data*,struct sk_buff*,int) ; 
 int* ieee802_1d_to_ac ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

void __ieee80211_tx_skb_tid_band(struct ieee80211_sub_if_data *sdata,
				 struct sk_buff *skb, int tid,
				 enum ieee80211_band band)
{
	int ac = ieee802_1d_to_ac[tid & 7];

	skb_set_mac_header(skb, 0);
	skb_set_network_header(skb, 0);
	skb_set_transport_header(skb, 0);

	skb_set_queue_mapping(skb, ac);
	skb->priority = tid;

	skb->dev = sdata->dev;

	/*
	 * The other path calling ieee80211_xmit is from the tasklet,
	 * and while we can handle concurrent transmissions locking
	 * requirements are that we do not come into tx with bhs on.
	 */
	local_bh_disable();
	ieee80211_xmit(sdata, skb, band);
	local_bh_enable();
}