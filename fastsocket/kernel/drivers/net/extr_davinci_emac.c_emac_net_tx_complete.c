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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct emac_priv {TYPE_1__ net_dev_stats; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int emac_net_tx_complete(struct emac_priv *priv,
				void **net_data_tokens,
				int num_tokens, u32 ch)
{
	u32 cnt;

	if (unlikely(num_tokens && netif_queue_stopped(priv->ndev)))
		netif_start_queue(priv->ndev);
	for (cnt = 0; cnt < num_tokens; cnt++) {
		struct sk_buff *skb = (struct sk_buff *)net_data_tokens[cnt];
		if (skb == NULL)
			continue;
		priv->net_dev_stats.tx_packets++;
		priv->net_dev_stats.tx_bytes += skb->len;
		dev_kfree_skb_any(skb);
	}
	return 0;
}