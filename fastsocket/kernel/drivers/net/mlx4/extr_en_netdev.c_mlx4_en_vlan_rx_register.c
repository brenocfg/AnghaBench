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
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; scalar_t__ port_up; struct vlan_group* vlgrp; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; scalar_t__ device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,struct vlan_group*) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_SET_VLAN_FLTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vlan_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_vlan_rx_register(struct net_device *dev, struct vlan_group *grp)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;

	en_dbg(HW, priv, "Registering VLAN group:%p\n", grp);
	priv->vlgrp = grp;

	mutex_lock(&mdev->state_lock);
	if (mdev->device_up && priv->port_up) {
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv->port, grp);
		if (err)
			en_err(priv, "Failed configuring VLAN filter\n");
	}
	mutex_unlock(&mdev->state_lock);
}