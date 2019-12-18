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
struct net_device {int /*<<< orphan*/  features; } ;
struct TYPE_2__ {int tx_type; int rx_filter; } ;
struct mlx4_en_priv {TYPE_1__ hwtstamp_config; scalar_t__ port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_RX ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 int mlx4_en_alloc_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_resources (struct mlx4_en_priv*) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_features_change (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

int mlx4_en_timestamp_config(struct net_device *dev, int tx_type, int rx_filter)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int port_up = 0;
	int err = 0;

	mutex_lock(&mdev->state_lock);
	if (priv->port_up) {
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	}

	mlx4_en_free_resources(priv);

	en_warn(priv, "Changing Time Stamp configuration\n");

	priv->hwtstamp_config.tx_type = tx_type;
	priv->hwtstamp_config.rx_filter = rx_filter;

	if (rx_filter != HWTSTAMP_FILTER_NONE)
		dev->features &= ~NETIF_F_HW_VLAN_RX;
	else
		dev->features |= NETIF_F_HW_VLAN_RX;

	err = mlx4_en_alloc_resources(priv);
	if (err) {
		en_err(priv, "Failed reallocating port resources\n");
		goto out;
	}
	if (port_up) {
		err = mlx4_en_start_port(dev);
		if (err)
			en_err(priv, "Failed starting port\n");
	}

out:
	mutex_unlock(&mdev->state_lock);
	netdev_features_change(dev);
	return err;
}