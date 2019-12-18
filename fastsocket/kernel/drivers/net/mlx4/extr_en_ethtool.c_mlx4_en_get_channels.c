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
struct mlx4_en_priv {int tx_ring_num; int /*<<< orphan*/  rx_ring_num; } ;
struct ethtool_channels {int tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RX_RINGS ; 
 int /*<<< orphan*/  MLX4_EN_MAX_TX_RING_P_UP ; 
 int MLX4_EN_NUM_UP ; 
 int /*<<< orphan*/  memset (struct ethtool_channels*,int /*<<< orphan*/ ,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_get_channels(struct net_device *dev,
				 struct ethtool_channels *channel)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	memset(channel, 0, sizeof(*channel));

	channel->max_rx = MAX_RX_RINGS;
	channel->max_tx = MLX4_EN_MAX_TX_RING_P_UP;

	channel->rx_count = priv->rx_ring_num;
	channel->tx_count = priv->tx_ring_num / MLX4_EN_NUM_UP;
}