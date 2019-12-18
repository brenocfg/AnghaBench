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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_tx_control {struct ieee80211_sta* sta; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_sta_info {int /*<<< orphan*/  pending_frames; } ;
struct ar9170 {int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/ * tx_pending; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  IS_STARTED (struct ar9170*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_tx (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_tx_accounting (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_tx_ampdu (struct ar9170*) ; 
 int carl9170_tx_ampdu_queue (struct ar9170*,struct ieee80211_sta*,struct sk_buff*,struct ieee80211_tx_info*) ; 
 int carl9170_tx_prepare (struct ar9170*,struct ieee80211_sta*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 unsigned int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void carl9170_op_tx(struct ieee80211_hw *hw,
		    struct ieee80211_tx_control *control,
		    struct sk_buff *skb)
{
	struct ar9170 *ar = hw->priv;
	struct ieee80211_tx_info *info;
	struct ieee80211_sta *sta = control->sta;
	bool run;

	if (unlikely(!IS_STARTED(ar)))
		goto err_free;

	info = IEEE80211_SKB_CB(skb);

	if (unlikely(carl9170_tx_prepare(ar, sta, skb)))
		goto err_free;

	carl9170_tx_accounting(ar, skb);
	/*
	 * from now on, one has to use carl9170_tx_status to free
	 * all ressouces which are associated with the frame.
	 */

	if (sta) {
		struct carl9170_sta_info *stai = (void *) sta->drv_priv;
		atomic_inc(&stai->pending_frames);
	}

	if (info->flags & IEEE80211_TX_CTL_AMPDU) {
		/* to static code analyzers and reviewers:
		 * mac80211 guarantees that a valid "sta"
		 * reference is present, if a frame is to
		 * be part of an ampdu. Hence any extra
		 * sta == NULL checks are redundant in this
		 * special case.
		 */
		run = carl9170_tx_ampdu_queue(ar, sta, skb, info);
		if (run)
			carl9170_tx_ampdu(ar);

	} else {
		unsigned int queue = skb_get_queue_mapping(skb);

		skb_queue_tail(&ar->tx_pending[queue], skb);
	}

	carl9170_tx(ar);
	return;

err_free:
	ar->tx_dropped++;
	ieee80211_free_txskb(ar->hw, skb);
}