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
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; } ;
struct cpmac_priv {int /*<<< orphan*/  ring_size; } ;

/* Variables and functions */
 int EBUSY ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int cpmac_set_ringparam(struct net_device *dev, struct ethtool_ringparam* ring)
{
	struct cpmac_priv *priv = netdev_priv(dev);

	if (netif_running(dev))
		return -EBUSY;
	priv->ring_size = ring->rx_pending;
	return 0;
}