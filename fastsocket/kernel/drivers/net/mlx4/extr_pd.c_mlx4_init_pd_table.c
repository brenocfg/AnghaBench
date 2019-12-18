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
struct mlx4_priv {int /*<<< orphan*/  pd_bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  reserved_pds; int /*<<< orphan*/  num_pds; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int NOT_MASKED_PD_BITS ; 
 int mlx4_bitmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_init_pd_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	return mlx4_bitmap_init(&priv->pd_bitmap, dev->caps.num_pds,
				(1 << NOT_MASKED_PD_BITS) - 1,
				 dev->caps.reserved_pds, 0);
}