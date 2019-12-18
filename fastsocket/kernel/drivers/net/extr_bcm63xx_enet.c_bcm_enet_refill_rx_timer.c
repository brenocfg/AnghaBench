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
struct net_device {int dummy; } ;
struct bcm_enet_priv {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_enet_refill_rx (struct net_device*) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm_enet_refill_rx_timer(unsigned long data)
{
	struct net_device *dev;
	struct bcm_enet_priv *priv;

	dev = (struct net_device *)data;
	priv = netdev_priv(dev);

	spin_lock(&priv->rx_lock);
	bcm_enet_refill_rx((struct net_device *)data);
	spin_unlock(&priv->rx_lock);
}