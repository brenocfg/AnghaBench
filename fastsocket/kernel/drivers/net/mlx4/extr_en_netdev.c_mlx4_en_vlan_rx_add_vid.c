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
struct mlx4_en_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  vlgrp; scalar_t__ port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; scalar_t__ device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,unsigned short,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_SET_VLAN_FLTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_register_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vlan_group_get_device (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void mlx4_en_vlan_rx_add_vid(struct net_device *dev, unsigned short vid)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;
	int idx;

	if (!priv->vlgrp)
		return;

	en_dbg(HW, priv, "adding VLAN:%d (vlgrp entry:%p)\n",
	       vid, vlan_group_get_device(priv->vlgrp, vid));

	/* Add VID to port VLAN filter */
	mutex_lock(&mdev->state_lock);
	if (mdev->device_up && priv->port_up) {
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv->port, priv->vlgrp);
		if (err)
			en_err(priv, "Failed configuring VLAN filter\n");
	}
	if (mlx4_register_vlan(mdev->dev, priv->port, vid, &idx))
		en_dbg(HW, priv, "failed adding vlan %d\n", vid);
	mutex_unlock(&mdev->state_lock);

}