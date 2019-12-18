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
struct stir_cb {int /*<<< orphan*/  thread; int /*<<< orphan*/  tx_pending; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SKB_LINEAR_ASSERT (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct stir_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ unlikely (struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t stir_hard_xmit(struct sk_buff *skb,
					struct net_device *netdev)
{
	struct stir_cb *stir = netdev_priv(netdev);

	netif_stop_queue(netdev);

	/* the IRDA wrapping routines don't deal with non linear skb */
	SKB_LINEAR_ASSERT(skb);

	skb = xchg(&stir->tx_pending, skb);
        wake_up_process(stir->thread);
	
	/* this should never happen unless stop/wakeup problem */
	if (unlikely(skb)) {
		WARN_ON(1);
		dev_kfree_skb(skb);
	}

	return NETDEV_TX_OK;
}