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
typedef  int /*<<< orphan*/  uint32_t ;
struct net_device {int flags; } ;
struct gfar_private {int device_flags; int /*<<< orphan*/  bflock; int /*<<< orphan*/  rx_csum_enable; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  txlock; int /*<<< orphan*/  rxlock; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FSL_GIANFAR_DEV_HAS_CSUM ; 
 int IFF_UP ; 
 int /*<<< orphan*/  gfar_clean_rx_ring (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_halt (struct net_device*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int startup_gfar (struct net_device*) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 

__attribute__((used)) static int gfar_set_rx_csum(struct net_device *dev, uint32_t data)
{
	struct gfar_private *priv = netdev_priv(dev);
	unsigned long flags;
	int err = 0;

	if (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_CSUM))
		return -EOPNOTSUPP;

	if (dev->flags & IFF_UP) {
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

	spin_lock_irqsave(&priv->bflock, flags);
	priv->rx_csum_enable = data;
	spin_unlock_irqrestore(&priv->bflock, flags);

	if (dev->flags & IFF_UP) {
		err = startup_gfar(dev);
		netif_wake_queue(dev);
	}
	return err;
}