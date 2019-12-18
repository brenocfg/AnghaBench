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
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* prof; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;

/* Variables and functions */
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_get_pauseparam(struct net_device *dev,
				 struct ethtool_pauseparam *pause)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	pause->tx_pause = priv->prof->tx_pause;
	pause->rx_pause = priv->prof->rx_pause;
}