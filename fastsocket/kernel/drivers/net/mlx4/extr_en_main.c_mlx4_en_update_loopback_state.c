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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int flags; scalar_t__ validate_loopback; TYPE_1__* mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MLX4_EN_FLAG_ENABLE_HW_LOOPBACK ; 
 int MLX4_EN_FLAG_RX_FILTER_NEEDED ; 
 scalar_t__ mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

void mlx4_en_update_loopback_state(struct net_device *dev, u32 features)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	priv->flags &= ~(MLX4_EN_FLAG_RX_FILTER_NEEDED|
			MLX4_EN_FLAG_ENABLE_HW_LOOPBACK);

	/* Drop the packet if SRIOV is not enabled
	 * and not performing the selftest or flb disabled
	 */
	if (mlx4_is_mfunc(priv->mdev->dev) && !priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_RX_FILTER_NEEDED;

	/* Set dmac in Tx WQE if we are in SRIOV mode or if loopback selftest
	 * is requested
	 */
	if (mlx4_is_mfunc(priv->mdev->dev) || priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_ENABLE_HW_LOOPBACK;
}