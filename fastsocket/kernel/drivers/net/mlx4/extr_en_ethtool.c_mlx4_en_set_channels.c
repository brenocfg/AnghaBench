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
struct mlx4_en_priv {int num_tx_rings_p_up; int tx_ring_num; scalar_t__ rx_ring_num; scalar_t__ port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; } ;
struct ethtool_channels {int tx_count; scalar_t__ rx_count; scalar_t__ combined_count; scalar_t__ other_count; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_RX_RINGS ; 
 int MLX4_EN_MAX_TX_RING_P_UP ; 
 int MLX4_EN_NUM_UP ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*,scalar_t__) ; 
 int mlx4_en_alloc_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_resources (struct mlx4_en_priv*) ; 
 int mlx4_en_moderation_update (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_setup_tc (struct net_device*,int) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 

__attribute__((used)) static int mlx4_en_set_channels(struct net_device *dev,
				struct ethtool_channels *channel)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int port_up;
	int err = 0;

	if (channel->other_count || channel->combined_count ||
	    channel->tx_count > MLX4_EN_MAX_TX_RING_P_UP ||
	    channel->rx_count > MAX_RX_RINGS ||
	    !channel->tx_count || !channel->rx_count)
		return -EINVAL;

	mutex_lock(&mdev->state_lock);
	if (priv->port_up) {
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	}

	mlx4_en_free_resources(priv);

	priv->num_tx_rings_p_up = channel->tx_count;
	priv->tx_ring_num = channel->tx_count * MLX4_EN_NUM_UP;
	priv->rx_ring_num = channel->rx_count;

	err = mlx4_en_alloc_resources(priv);
	if (err) {
		en_err(priv, "Failed reallocating port resources\n");
		goto out;
	}

	netif_set_real_num_tx_queues(dev, priv->tx_ring_num);
	netif_set_real_num_rx_queues(dev, priv->rx_ring_num);

	mlx4_en_setup_tc(dev, MLX4_EN_NUM_UP);

	en_warn(priv, "Using %d TX rings\n", priv->tx_ring_num);
	en_warn(priv, "Using %d RX rings\n", priv->rx_ring_num);

	if (port_up) {
		err = mlx4_en_start_port(dev);
		if (err)
			en_err(priv, "Failed starting port\n");
	}

	err = mlx4_en_moderation_update(priv);

out:
	mutex_unlock(&mdev->state_lock);
	return err;
}