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
struct sc92031_priv {scalar_t__ tx_head; scalar_t__ tx_tail; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 struct sc92031_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void _sc92031_tx_clear(struct net_device *dev)
{
	struct sc92031_priv *priv = netdev_priv(dev);

	while (priv->tx_head - priv->tx_tail > 0) {
		priv->tx_tail++;
		dev->stats.tx_dropped++;
	}
	priv->tx_head = priv->tx_tail = 0;
}