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
typedef  int u32 ;
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  iif; scalar_t__ len; scalar_t__ tc_verd; } ;
struct netdev_queue {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  ifindex; struct net_device_stats stats; } ;
struct ifb_private {int tasklet_pending; int /*<<< orphan*/  ifb_tasklet; int /*<<< orphan*/  st_rxq_rsch; int /*<<< orphan*/  rq; int /*<<< orphan*/  st_rxq_check; int /*<<< orphan*/  st_rx_frm_ing; int /*<<< orphan*/  st_rx_frm_egr; int /*<<< orphan*/  tq; int /*<<< orphan*/  st_rxq_notenter; int /*<<< orphan*/  st_rx2tx_tran; int /*<<< orphan*/  st_rxq_enter; int /*<<< orphan*/  st_txq_refl_try; int /*<<< orphan*/  st_task_enter; } ;
struct TYPE_3__ {int /*<<< orphan*/  hard_header_len; } ;

/* Variables and functions */
 int AT_EGRESS ; 
 int AT_INGRESS ; 
 int /*<<< orphan*/  BUG () ; 
 int G_TC_FROM (scalar_t__) ; 
 scalar_t__ SET_TC_NCLS (scalar_t__) ; 
 scalar_t__ __netif_tx_trylock (struct netdev_queue*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 TYPE_1__* dev_get_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_put (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  init_net ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ifb_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ri_tasklet(unsigned long dev)
{

	struct net_device *_dev = (struct net_device *)dev;
	struct ifb_private *dp = netdev_priv(_dev);
	struct net_device_stats *stats = &_dev->stats;
	struct netdev_queue *txq;
	struct sk_buff *skb;

	txq = netdev_get_tx_queue(_dev, 0);
	dp->st_task_enter++;
	if ((skb = skb_peek(&dp->tq)) == NULL) {
		dp->st_txq_refl_try++;
		if (__netif_tx_trylock(txq)) {
			dp->st_rxq_enter++;
			while ((skb = skb_dequeue(&dp->rq)) != NULL) {
				skb_queue_tail(&dp->tq, skb);
				dp->st_rx2tx_tran++;
			}
			__netif_tx_unlock(txq);
		} else {
			/* reschedule */
			dp->st_rxq_notenter++;
			goto resched;
		}
	}

	while ((skb = skb_dequeue(&dp->tq)) != NULL) {
		u32 from = G_TC_FROM(skb->tc_verd);

		skb->tc_verd = 0;
		skb->tc_verd = SET_TC_NCLS(skb->tc_verd);
		stats->tx_packets++;
		stats->tx_bytes +=skb->len;

		skb->dev = dev_get_by_index(&init_net, skb->iif);
		if (!skb->dev) {
			dev_kfree_skb(skb);
			stats->tx_dropped++;
			break;
		}
		dev_put(skb->dev);
		skb->iif = _dev->ifindex;

		if (from & AT_EGRESS) {
			dp->st_rx_frm_egr++;
			dev_queue_xmit(skb);
		} else if (from & AT_INGRESS) {
			dp->st_rx_frm_ing++;
			skb_pull(skb, skb->dev->hard_header_len);
			netif_rx(skb);
		} else
			BUG();
	}

	if (__netif_tx_trylock(txq)) {
		dp->st_rxq_check++;
		if ((skb = skb_peek(&dp->rq)) == NULL) {
			dp->tasklet_pending = 0;
			if (netif_queue_stopped(_dev))
				netif_wake_queue(_dev);
		} else {
			dp->st_rxq_rsch++;
			__netif_tx_unlock(txq);
			goto resched;
		}
		__netif_tx_unlock(txq);
	} else {
resched:
		dp->tasklet_pending = 1;
		tasklet_schedule(&dp->ifb_tasklet);
	}

}