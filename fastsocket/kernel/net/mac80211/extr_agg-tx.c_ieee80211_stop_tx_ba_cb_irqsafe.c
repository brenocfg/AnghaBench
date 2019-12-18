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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  cb; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; int /*<<< orphan*/  skb_queue; struct ieee80211_local* local; } ;
struct ieee80211_ra_tid {int /*<<< orphan*/  tid; int /*<<< orphan*/  ra; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_SDATA_QUEUE_AGG_STOP ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_stop_tx_ba_cb_irqsafe(struct ieee80211_vif *vif,
				     const u8 *ra, u16 tid)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_ra_tid *ra_tid;
	struct sk_buff *skb = dev_alloc_skb(0);

	if (unlikely(!skb))
		return;

	ra_tid = (struct ieee80211_ra_tid *) &skb->cb;
	memcpy(&ra_tid->ra, ra, ETH_ALEN);
	ra_tid->tid = tid;

	skb->pkt_type = IEEE80211_SDATA_QUEUE_AGG_STOP;
	skb_queue_tail(&sdata->skb_queue, skb);
	ieee80211_queue_work(&local->hw, &sdata->work);
}