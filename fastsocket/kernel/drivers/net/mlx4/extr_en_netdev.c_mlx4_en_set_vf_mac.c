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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_mac_to_u64 (int /*<<< orphan*/ *) ; 
 int mlx4_set_vf_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_vf_mac(struct net_device *dev, int queue, u8 *mac)
{
	struct mlx4_en_priv *en_priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = en_priv->mdev;
	u64 mac_u64 = mlx4_en_mac_to_u64(mac);

	if (!is_valid_ether_addr(mac))
		return -EINVAL;

	return mlx4_set_vf_mac(mdev->dev, en_priv->port, queue, mac_u64);
}