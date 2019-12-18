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
struct meth_private {int tx_count; } ;

/* Variables and functions */
 int TX_RING_ENTRIES ; 
 struct meth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int meth_tx_full(struct net_device *dev)
{
	struct meth_private *priv = netdev_priv(dev);

	return (priv->tx_count >= TX_RING_ENTRIES - 1);
}