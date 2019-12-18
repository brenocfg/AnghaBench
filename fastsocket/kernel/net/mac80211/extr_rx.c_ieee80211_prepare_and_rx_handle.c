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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  name; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  rx_flags; } ;
struct ieee80211_rx_data {struct sk_buff* skb; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_RX_RA_MATCH ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_invoke_rx_handlers (struct ieee80211_rx_data*) ; 
 scalar_t__ net_ratelimit () ; 
 int prepare_for_handlers (struct ieee80211_rx_data*,struct ieee80211_hdr*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_prepare_and_rx_handle(struct ieee80211_rx_data *rx,
					    struct sk_buff *skb, bool consume)
{
	struct ieee80211_local *local = rx->local;
	struct ieee80211_sub_if_data *sdata = rx->sdata;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr = (void *)skb->data;
	int prepares;

	rx->skb = skb;
	status->rx_flags |= IEEE80211_RX_RA_MATCH;
	prepares = prepare_for_handlers(rx, hdr);

	if (!prepares)
		return false;

	if (!consume) {
		skb = skb_copy(skb, GFP_ATOMIC);
		if (!skb) {
			if (net_ratelimit())
				wiphy_debug(local->hw.wiphy,
					"failed to copy skb for %s\n",
					sdata->name);
			return true;
		}

		rx->skb = skb;
	}

	ieee80211_invoke_rx_handlers(rx);
	return true;
}