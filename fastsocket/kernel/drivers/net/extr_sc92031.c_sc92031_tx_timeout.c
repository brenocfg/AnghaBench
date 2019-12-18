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
struct sc92031_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_timeouts; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _sc92031_reset (struct net_device*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sc92031_disable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  sc92031_enable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc92031_tx_timeout(struct net_device *dev)
{
	struct sc92031_priv *priv = netdev_priv(dev);

	/* Disable interrupts by clearing the interrupt mask.*/
	sc92031_disable_interrupts(dev);

	spin_lock(&priv->lock);

	priv->tx_timeouts++;

	_sc92031_reset(dev);
	mmiowb();

	spin_unlock(&priv->lock);

	/* enable interrupts */
	sc92031_enable_interrupts(dev);

	if (netif_carrier_ok(dev))
		netif_wake_queue(dev);
}