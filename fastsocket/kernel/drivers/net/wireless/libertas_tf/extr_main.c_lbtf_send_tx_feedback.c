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
struct txpd {int dummy; } ;
struct lbtf_private {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  bc_ps_buf; int /*<<< orphan*/  skb_to_tx; int /*<<< orphan*/ * tx_skb; } ;
struct ieee80211_tx_info {int flags; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ *) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

void lbtf_send_tx_feedback(struct lbtf_private *priv, u8 retrycnt, u8 fail)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(priv->tx_skb);

	ieee80211_tx_info_clear_status(info);
	/*
	 * Commented out, otherwise we never go beyond 1Mbit/s using mac80211
	 * default pid rc algorithm.
	 *
	 * info->status.retry_count = MRVL_DEFAULT_RETRIES - retrycnt;
	 */
	if (!(info->flags & IEEE80211_TX_CTL_NO_ACK) && !fail)
		info->flags |= IEEE80211_TX_STAT_ACK;
	skb_pull(priv->tx_skb, sizeof(struct txpd));
	ieee80211_tx_status_irqsafe(priv->hw, priv->tx_skb);
	priv->tx_skb = NULL;
	if (!priv->skb_to_tx && skb_queue_empty(&priv->bc_ps_buf))
		ieee80211_wake_queues(priv->hw);
	else
		queue_work(lbtf_wq, &priv->tx_work);
}