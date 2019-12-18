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
struct mlx4_en_priv {int /*<<< orphan*/  vlgrp; int /*<<< orphan*/  port; scalar_t__ port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; scalar_t__ device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,unsigned short,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_SET_VLAN_FLTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_find_cached_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int*) ; 
 int /*<<< orphan*/  mlx4_unregister_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vlan_group_get_device (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  vlan_group_set_device (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_en_vlan_rx_kill_vid(struct net_device *dev, unsigned short vid)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;
	int idx;

	if (!priv->vlgrp)
		return;

	en_dbg(HW, priv, "Killing VID:%d (vlgrp:%p vlgrp entry:%p)\n",
	       vid, priv->vlgrp, vlan_group_get_device(priv->vlgrp, vid));
	vlan_group_set_device(priv->vlgrp, vid, NULL);

	/* Remove VID from port VLAN filter */
	mutex_lock(&mdev->state_lock);
	if (!mlx4_find_cached_vlan(mdev->dev, priv->port, vid, &idx))
		mlx4_unregister_vlan(mdev->dev, priv->port, idx);
	else
		en_dbg(HW, priv, "could not find vid %d in cache\n", vid);

	if (mdev->device_up && priv->port_up) {
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv->port, priv->vlgrp);
		if (err)
			en_err(priv, "Failed configuring VLAN filter\n");
	}
	mutex_unlock(&mdev->state_lock);
}