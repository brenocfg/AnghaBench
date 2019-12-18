#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct lbtf_private {TYPE_1__* vif; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  bc_ps_buf; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct sk_buff* ieee80211_get_buffered_bc (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lbtf_beacon_set (struct lbtf_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  lbtf_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void lbtf_bcn_sent(struct lbtf_private *priv)
{
	struct sk_buff *skb = NULL;

	if (priv->vif->type != NL80211_IFTYPE_AP)
		return;

	if (skb_queue_empty(&priv->bc_ps_buf)) {
		bool tx_buff_bc = false;

		while ((skb = ieee80211_get_buffered_bc(priv->hw, priv->vif))) {
			skb_queue_tail(&priv->bc_ps_buf, skb);
			tx_buff_bc = true;
		}
		if (tx_buff_bc) {
			ieee80211_stop_queues(priv->hw);
			queue_work(lbtf_wq, &priv->tx_work);
		}
	}

	skb = ieee80211_beacon_get(priv->hw, priv->vif);

	if (skb) {
		lbtf_beacon_set(priv, skb);
		kfree_skb(skb);
	}
}