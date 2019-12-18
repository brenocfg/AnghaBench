#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlx4_en_priv {int tx_ring_num; int rx_ring_num; TYPE_2__* rx_ring; TYPE_1__* tx_ring; int /*<<< orphan*/  port_stats; int /*<<< orphan*/  pkstats; int /*<<< orphan*/  pstats; int /*<<< orphan*/  stats; int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ packets; scalar_t__ bytes; } ;
struct TYPE_3__ {scalar_t__ packets; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_en_DUMP_ETH_STATS (struct mlx4_en_dev*,int /*<<< orphan*/ ,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_clear_stats(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int i;

	if (mlx4_en_DUMP_ETH_STATS(mdev, priv->port, 1))
		en_dbg(HW, priv, "Failed dumping statistics\n");

	memset(&priv->stats, 0, sizeof(priv->stats));
	memset(&priv->pstats, 0, sizeof(priv->pstats));
	memset(&priv->pkstats, 0, sizeof(priv->pkstats));
	memset(&priv->port_stats, 0, sizeof(priv->port_stats));

	for (i = 0; i < priv->tx_ring_num; i++) {
		priv->tx_ring[i].bytes = 0;
		priv->tx_ring[i].packets = 0;
	}
	for (i = 0; i < priv->rx_ring_num; i++) {
		priv->rx_ring[i].bytes = 0;
		priv->rx_ring[i].packets = 0;
	}
}