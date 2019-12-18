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
struct sk_buff {struct sk_buff* next; } ;
struct net_device {int features; } ;
struct TYPE_2__ {int tx_dropped; } ;
struct myri10ge_slice_state {TYPE_1__ stats; } ;
struct myri10ge_priv {struct myri10ge_slice_state* ss; } ;
typedef  scalar_t__ netdev_tx_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ NETDEV_TX_OK ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ myri10ge_xmit (struct sk_buff*,struct net_device*) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t myri10ge_sw_tso(struct sk_buff *skb,
					 struct net_device *dev)
{
	struct sk_buff *segs, *curr;
	struct myri10ge_priv *mgp = netdev_priv(dev);
	struct myri10ge_slice_state *ss;
	netdev_tx_t status;

	segs = skb_gso_segment(skb, dev->features & ~NETIF_F_TSO6);
	if (IS_ERR(segs))
		goto drop;

	while (segs) {
		curr = segs;
		segs = segs->next;
		curr->next = NULL;
		status = myri10ge_xmit(curr, dev);
		if (status != 0) {
			dev_kfree_skb_any(curr);
			if (segs != NULL) {
				curr = segs;
				segs = segs->next;
				curr->next = NULL;
				dev_kfree_skb_any(segs);
			}
			goto drop;
		}
	}
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;

drop:
	ss = &mgp->ss[skb_get_queue_mapping(skb)];
	dev_kfree_skb_any(skb);
	ss->stats.tx_dropped += 1;
	return NETDEV_TX_OK;
}