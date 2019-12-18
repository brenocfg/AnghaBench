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
struct mlx4_en_priv {scalar_t__ rx_frames; scalar_t__ rx_usecs; scalar_t__ tx_usecs; scalar_t__ tx_frames; int /*<<< orphan*/  adaptive_rx_coal; int /*<<< orphan*/  sample_interval; int /*<<< orphan*/  rx_usecs_high; int /*<<< orphan*/  pkt_rate_high; int /*<<< orphan*/  rx_usecs_low; int /*<<< orphan*/  pkt_rate_low; } ;
struct ethtool_coalesce {scalar_t__ rx_max_coalesced_frames; scalar_t__ rx_coalesce_usecs; scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames; int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  rate_sample_interval; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  pkt_rate_high; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  pkt_rate_low; } ;

/* Variables and functions */
 scalar_t__ MLX4_EN_AUTO_CONF ; 
 scalar_t__ MLX4_EN_RX_COAL_TARGET ; 
 scalar_t__ MLX4_EN_RX_COAL_TIME ; 
 int mlx4_en_moderation_update (struct mlx4_en_priv*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_coalesce(struct net_device *dev,
			      struct ethtool_coalesce *coal)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	priv->rx_frames = (coal->rx_max_coalesced_frames ==
			   MLX4_EN_AUTO_CONF) ?
				MLX4_EN_RX_COAL_TARGET :
				coal->rx_max_coalesced_frames;
	priv->rx_usecs = (coal->rx_coalesce_usecs ==
			  MLX4_EN_AUTO_CONF) ?
				MLX4_EN_RX_COAL_TIME :
				coal->rx_coalesce_usecs;

	/* Setting TX coalescing parameters */
	if (coal->tx_coalesce_usecs != priv->tx_usecs ||
	    coal->tx_max_coalesced_frames != priv->tx_frames) {
		priv->tx_usecs = coal->tx_coalesce_usecs;
		priv->tx_frames = coal->tx_max_coalesced_frames;
	}

	/* Set adaptive coalescing params */
	priv->pkt_rate_low = coal->pkt_rate_low;
	priv->rx_usecs_low = coal->rx_coalesce_usecs_low;
	priv->pkt_rate_high = coal->pkt_rate_high;
	priv->rx_usecs_high = coal->rx_coalesce_usecs_high;
	priv->sample_interval = coal->rate_sample_interval;
	priv->adaptive_rx_coal = coal->use_adaptive_rx_coalesce;

	return mlx4_en_moderation_update(priv);
}