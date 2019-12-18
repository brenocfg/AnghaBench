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
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_sleep; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct bnep_session {TYPE_1__* sock; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BNEP_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ bnep_net_mc_filter (struct sk_buff*,struct bnep_session*) ; 
 scalar_t__ bnep_net_proto_filter (struct sk_buff*,struct bnep_session*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct bnep_session* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bnep_net_xmit(struct sk_buff *skb,
				 struct net_device *dev)
{
	struct bnep_session *s = netdev_priv(dev);
	struct sock *sk = s->sock->sk;

	BT_DBG("skb %p, dev %p", skb, dev);

#ifdef CONFIG_BT_BNEP_MC_FILTER
	if (bnep_net_mc_filter(skb, s)) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
#endif

#ifdef CONFIG_BT_BNEP_PROTO_FILTER
	if (bnep_net_proto_filter(skb, s)) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
#endif

	/*
	 * We cannot send L2CAP packets from here as we are potentially in a bh.
	 * So we have to queue them and wake up session thread which is sleeping
	 * on the sk->sk_sleep.
	 */
	dev->trans_start = jiffies;
	skb_queue_tail(&sk->sk_write_queue, skb);
	wake_up_interruptible(sk->sk_sleep);

	if (skb_queue_len(&sk->sk_write_queue) >= BNEP_TX_QUEUE_LEN) {
		BT_DBG("tx queue is full");

		/* Stop queuing.
		 * Session thread will do netif_wake_queue() */
		netif_stop_queue(dev);
	}

	return NETDEV_TX_OK;
}