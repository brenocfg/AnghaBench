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
struct octeon_ethernet {TYPE_1__* tx_free_list; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cvm_oct_tx_shutdown(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	unsigned long flags;
	int qos;

	for (qos = 0; qos < 16; qos++) {
		spin_lock_irqsave(&priv->tx_free_list[qos].lock, flags);
		while (skb_queue_len(&priv->tx_free_list[qos]))
			dev_kfree_skb_any(__skb_dequeue
					  (&priv->tx_free_list[qos]));
		spin_unlock_irqrestore(&priv->tx_free_list[qos].lock, flags);
	}
}