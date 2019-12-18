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
struct sk_buff {int priority; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vif; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_1__ control; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_INTFL_NEED_TXPROCESSING ; 
 int /*<<< orphan*/  ieee80211_mps_set_frame_flags (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_set_qos_hdr (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_frame_for_deferred_tx(struct ieee80211_sub_if_data *sdata,
		struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;

	skb_set_mac_header(skb, 0);
	skb_set_network_header(skb, 0);
	skb_set_transport_header(skb, 0);

	/* Send all internal mgmt frames on VO. Accordingly set TID to 7. */
	skb_set_queue_mapping(skb, IEEE80211_AC_VO);
	skb->priority = 7;

	info->control.vif = &sdata->vif;
	info->flags |= IEEE80211_TX_INTFL_NEED_TXPROCESSING;
	ieee80211_set_qos_hdr(sdata, skb);
	ieee80211_mps_set_frame_flags(sdata, NULL, hdr);
}