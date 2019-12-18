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
struct tid_ampdu_rx {int /*<<< orphan*/  head_seq_num; struct sk_buff** reorder_buf; int /*<<< orphan*/  stored_mpdu_num; int /*<<< orphan*/  reorder_lock; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  rx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RX_DEFERRED_RELEASE ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_sn_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_release_reorder_frame(struct ieee80211_sub_if_data *sdata,
					    struct tid_ampdu_rx *tid_agg_rx,
					    int index,
					    struct sk_buff_head *frames)
{
	struct sk_buff *skb = tid_agg_rx->reorder_buf[index];
	struct ieee80211_rx_status *status;

	lockdep_assert_held(&tid_agg_rx->reorder_lock);

	if (!skb)
		goto no_frame;

	/* release the frame from the reorder ring buffer */
	tid_agg_rx->stored_mpdu_num--;
	tid_agg_rx->reorder_buf[index] = NULL;
	status = IEEE80211_SKB_RXCB(skb);
	status->rx_flags |= IEEE80211_RX_DEFERRED_RELEASE;
	__skb_queue_tail(frames, skb);

no_frame:
	tid_agg_rx->head_seq_num = ieee80211_sn_inc(tid_agg_rx->head_seq_num);
}