#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlx4_en_priv {int tx_ring_num; int rx_ring_num; TYPE_3__* mdev; int /*<<< orphan*/  stats_bitmap; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int MLX4_DEV_CAP_FLAG_UC_LOOPBACK ; 
 int /*<<< orphan*/  MLX4_EN_NUM_SELF_TEST ; 
 int NUM_ALL_STATS ; 
 int hweight64 (int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_sset_count(struct net_device *dev, int sset)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int bit_count = hweight64(priv->stats_bitmap);

	switch (sset) {
	case ETH_SS_STATS:
		return (priv->stats_bitmap ? bit_count : NUM_ALL_STATS) +
			(priv->tx_ring_num + priv->rx_ring_num) * 2;
	case ETH_SS_TEST:
		return MLX4_EN_NUM_SELF_TEST - !(priv->mdev->dev->caps.flags
					& MLX4_DEV_CAP_FLAG_UC_LOOPBACK) * 2;
	default:
		return -EOPNOTSUPP;
	}
}