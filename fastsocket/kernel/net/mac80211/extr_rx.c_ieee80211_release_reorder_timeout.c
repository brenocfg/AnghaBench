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
struct tid_ampdu_rx {int /*<<< orphan*/  reorder_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tid_rx; } ;
struct sta_info {int /*<<< orphan*/  sdata; TYPE_1__ ampdu_mlme; int /*<<< orphan*/  local; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_rx_data {int security_idx; int seqno_idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  local; int /*<<< orphan*/  sdata; struct sta_info* sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_rx_handlers (struct ieee80211_rx_data*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_sta_reorder_release (int /*<<< orphan*/ ,struct tid_ampdu_rx*,struct sk_buff_head*) ; 
 struct tid_ampdu_rx* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_release_reorder_timeout(struct sta_info *sta, int tid)
{
	struct sk_buff_head frames;
	struct ieee80211_rx_data rx = {
		.sta = sta,
		.sdata = sta->sdata,
		.local = sta->local,
		/* This is OK -- must be QoS data frame */
		.security_idx = tid,
		.seqno_idx = tid,
		.flags = 0,
	};
	struct tid_ampdu_rx *tid_agg_rx;

	tid_agg_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
	if (!tid_agg_rx)
		return;

	__skb_queue_head_init(&frames);

	spin_lock(&tid_agg_rx->reorder_lock);
	ieee80211_sta_reorder_release(sta->sdata, tid_agg_rx, &frames);
	spin_unlock(&tid_agg_rx->reorder_lock);

	ieee80211_rx_handlers(&rx, &frames);
}