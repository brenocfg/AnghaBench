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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_rss_map {scalar_t__ base_qpn; TYPE_1__* qps; } ;
struct mlx4_en_priv {size_t rx_ring_num; TYPE_2__* prof; struct mlx4_en_rss_map rss_map; } ;
struct TYPE_4__ {int rss_rings; } ;
struct TYPE_3__ {scalar_t__ qpn; } ;

/* Variables and functions */
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_rxfh_indir(struct net_device *dev, u32 *ring_index)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_rss_map *rss_map = &priv->rss_map;
	int rss_rings;
	size_t n = priv->rx_ring_num;
	int err = 0;

	rss_rings = priv->prof->rss_rings ?: priv->rx_ring_num;

	while (n--) {
		ring_index[n] = rss_map->qps[n % rss_rings].qpn -
			rss_map->base_qpn;
	}

	return err;
}