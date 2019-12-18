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
struct net_device {int flags; int /*<<< orphan*/  name; } ;
struct gfar_private {scalar_t__ rx_ring_size; scalar_t__ tx_ring_size; scalar_t__ num_txbdfree; int /*<<< orphan*/  txlock; int /*<<< orphan*/  rxlock; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GFAR_RX_MAX_RING_SIZE ; 
 scalar_t__ GFAR_TX_MAX_RING_SIZE ; 
 int IFF_UP ; 
 int /*<<< orphan*/  gfar_clean_rx_ring (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  gfar_halt (struct net_device*) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int startup_gfar (struct net_device*) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 

__attribute__((used)) static int gfar_sringparam(struct net_device *dev, struct ethtool_ringparam *rvals)
{
	struct gfar_private *priv = netdev_priv(dev);
	int err = 0;

	if (rvals->rx_pending > GFAR_RX_MAX_RING_SIZE)
		return -EINVAL;

	if (!is_power_of_2(rvals->rx_pending)) {
		printk("%s: Ring sizes must be a power of 2\n",
				dev->name);
		return -EINVAL;
	}

	if (rvals->tx_pending > GFAR_TX_MAX_RING_SIZE)
		return -EINVAL;

	if (!is_power_of_2(rvals->tx_pending)) {
		printk("%s: Ring sizes must be a power of 2\n",
				dev->name);
		return -EINVAL;
	}

	if (dev->flags & IFF_UP) {
		unsigned long flags;

		/* Halt TX and RX, and process the frames which
		 * have already been received */
		spin_lock_irqsave(&priv->txlock, flags);
		spin_lock(&priv->rxlock);

		gfar_halt(dev);

		spin_unlock(&priv->rxlock);
		spin_unlock_irqrestore(&priv->txlock, flags);

		gfar_clean_rx_ring(dev, priv->rx_ring_size);

		/* Now we take down the rings to rebuild them */
		stop_gfar(dev);
	}

	/* Change the size */
	priv->rx_ring_size = rvals->rx_pending;
	priv->tx_ring_size = rvals->tx_pending;
	priv->num_txbdfree = priv->tx_ring_size;

	/* Rebuild the rings with the new size */
	if (dev->flags & IFF_UP) {
		err = startup_gfar(dev);
		netif_wake_queue(dev);
	}
	return err;
}