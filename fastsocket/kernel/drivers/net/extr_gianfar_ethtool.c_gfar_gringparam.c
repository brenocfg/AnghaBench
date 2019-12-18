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
struct gfar_private {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_mini_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; void* rx_jumbo_max_pending; void* rx_mini_max_pending; void* rx_max_pending; } ;

/* Variables and functions */
 void* GFAR_RX_MAX_RING_SIZE ; 
 int /*<<< orphan*/  GFAR_TX_MAX_RING_SIZE ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gfar_gringparam(struct net_device *dev, struct ethtool_ringparam *rvals)
{
	struct gfar_private *priv = netdev_priv(dev);

	rvals->rx_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->rx_mini_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->rx_jumbo_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->tx_max_pending = GFAR_TX_MAX_RING_SIZE;

	/* Values changeable by the user.  The valid values are
	 * in the range 1 to the "*_max_pending" counterpart above.
	 */
	rvals->rx_pending = priv->rx_ring_size;
	rvals->rx_mini_pending = priv->rx_ring_size;
	rvals->rx_jumbo_pending = priv->rx_ring_size;
	rvals->tx_pending = priv->tx_ring_size;
}