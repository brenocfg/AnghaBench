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
struct netpoll_info {int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  arp_tx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_flags; int /*<<< orphan*/  rx_np; } ;
struct netpoll {TYPE_1__* dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_netpoll_cleanup ) (TYPE_1__*) ;} ;
struct TYPE_2__ {struct netpoll_info* npinfo; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPOLL_RX_ENABLED ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_rearming_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct netpoll_info*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct netpoll_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  synchronize_rcu_bh () ; 

void __netpoll_cleanup(struct netpoll *np)
{
	struct netpoll_info *npinfo;
	unsigned long flags;

	npinfo = np->dev->npinfo;
	if (!npinfo)
		return;

	if (!npinfo->rx_np) {
		spin_lock_irqsave(&npinfo->rx_lock, flags);
		npinfo->rx_flags &= ~NETPOLL_RX_ENABLED;
		spin_unlock_irqrestore(&npinfo->rx_lock, flags);
	}

	if (atomic_dec_and_test(&npinfo->refcnt)) {
		const struct net_device_ops *ops;

		ops = np->dev->netdev_ops;
		if (ops->ndo_netpoll_cleanup)
			ops->ndo_netpoll_cleanup(np->dev);

		rcu_assign_pointer(np->dev->npinfo, NULL);

		/* avoid racing with NAPI reading npinfo */
		synchronize_rcu_bh();

		skb_queue_purge(&npinfo->arp_tx);
		skb_queue_purge(&npinfo->txq);
		cancel_rearming_delayed_work(&npinfo->tx_work);

		/* clean after last, unfinished work */
		__skb_queue_purge(&npinfo->txq);
		kfree(npinfo);
	}
}