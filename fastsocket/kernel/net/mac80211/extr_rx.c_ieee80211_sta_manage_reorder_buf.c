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
typedef  int u16 ;
struct tid_ampdu_rx {int buf_size; int head_seq_num; int ssn; scalar_t__ stored_mpdu_num; int /*<<< orphan*/  reorder_lock; int /*<<< orphan*/ * reorder_time; struct sk_buff** reorder_buf; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; } ;

/* Variables and functions */
 int IEEE80211_SCTL_SEQ ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_release_reorder_frames (struct ieee80211_sub_if_data*,struct tid_ampdu_rx*,int,struct sk_buff_head*) ; 
 void* ieee80211_sn_inc (int) ; 
 scalar_t__ ieee80211_sn_less (int,int) ; 
 int ieee80211_sn_sub (int,int) ; 
 int /*<<< orphan*/  ieee80211_sta_reorder_release (struct ieee80211_sub_if_data*,struct tid_ampdu_rx*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  jiffies ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ieee80211_sta_manage_reorder_buf(struct ieee80211_sub_if_data *sdata,
					     struct tid_ampdu_rx *tid_agg_rx,
					     struct sk_buff *skb,
					     struct sk_buff_head *frames)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	u16 sc = le16_to_cpu(hdr->seq_ctrl);
	u16 mpdu_seq_num = (sc & IEEE80211_SCTL_SEQ) >> 4;
	u16 head_seq_num, buf_size;
	int index;
	bool ret = true;

	spin_lock(&tid_agg_rx->reorder_lock);

	buf_size = tid_agg_rx->buf_size;
	head_seq_num = tid_agg_rx->head_seq_num;

	/* frame with out of date sequence number */
	if (ieee80211_sn_less(mpdu_seq_num, head_seq_num)) {
		dev_kfree_skb(skb);
		goto out;
	}

	/*
	 * If frame the sequence number exceeds our buffering window
	 * size release some previous frames to make room for this one.
	 */
	if (!ieee80211_sn_less(mpdu_seq_num, head_seq_num + buf_size)) {
		head_seq_num = ieee80211_sn_inc(
				ieee80211_sn_sub(mpdu_seq_num, buf_size));
		/* release stored frames up to new head to stack */
		ieee80211_release_reorder_frames(sdata, tid_agg_rx,
						 head_seq_num, frames);
	}

	/* Now the new frame is always in the range of the reordering buffer */

	index = ieee80211_sn_sub(mpdu_seq_num,
				 tid_agg_rx->ssn) % tid_agg_rx->buf_size;

	/* check if we already stored this frame */
	if (tid_agg_rx->reorder_buf[index]) {
		dev_kfree_skb(skb);
		goto out;
	}

	/*
	 * If the current MPDU is in the right order and nothing else
	 * is stored we can process it directly, no need to buffer it.
	 * If it is first but there's something stored, we may be able
	 * to release frames after this one.
	 */
	if (mpdu_seq_num == tid_agg_rx->head_seq_num &&
	    tid_agg_rx->stored_mpdu_num == 0) {
		tid_agg_rx->head_seq_num =
			ieee80211_sn_inc(tid_agg_rx->head_seq_num);
		ret = false;
		goto out;
	}

	/* put the frame in the reordering buffer */
	tid_agg_rx->reorder_buf[index] = skb;
	tid_agg_rx->reorder_time[index] = jiffies;
	tid_agg_rx->stored_mpdu_num++;
	ieee80211_sta_reorder_release(sdata, tid_agg_rx, frames);

 out:
	spin_unlock(&tid_agg_rx->reorder_lock);
	return ret;
}