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
struct mlx4_en_priv {int /*<<< orphan*/  adaptive_rx_coal; int /*<<< orphan*/  sample_interval; int /*<<< orphan*/  rx_usecs_high; int /*<<< orphan*/  pkt_rate_high; int /*<<< orphan*/  rx_usecs_low; int /*<<< orphan*/  pkt_rate_low; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_usecs; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_usecs; } ;
struct ethtool_coalesce {int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  rate_sample_interval; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  pkt_rate_high; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  pkt_rate_low; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_coalesce(struct net_device *dev,
			      struct ethtool_coalesce *coal)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	coal->tx_coalesce_usecs = priv->tx_usecs;
	coal->tx_max_coalesced_frames = priv->tx_frames;
	coal->rx_coalesce_usecs = priv->rx_usecs;
	coal->rx_max_coalesced_frames = priv->rx_frames;

	coal->pkt_rate_low = priv->pkt_rate_low;
	coal->rx_coalesce_usecs_low = priv->rx_usecs_low;
	coal->pkt_rate_high = priv->pkt_rate_high;
	coal->rx_coalesce_usecs_high = priv->rx_usecs_high;
	coal->rate_sample_interval = priv->sample_interval;
	coal->use_adaptive_rx_coalesce = priv->adaptive_rx_coal;
	return 0;
}