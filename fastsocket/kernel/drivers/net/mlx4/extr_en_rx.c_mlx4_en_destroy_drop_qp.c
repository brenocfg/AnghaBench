#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  qpn; } ;
struct mlx4_en_priv {TYPE_1__* mdev; TYPE_2__ drop_qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_qp_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_qp_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

void mlx4_en_destroy_drop_qp(struct mlx4_en_priv *priv)
{
	u32 qpn;

	qpn = priv->drop_qp.qpn;
	mlx4_qp_remove(priv->mdev->dev, &priv->drop_qp);
	mlx4_qp_free(priv->mdev->dev, &priv->drop_qp);
	mlx4_qp_release_range(priv->mdev->dev, qpn, 1);
}