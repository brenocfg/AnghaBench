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
struct TYPE_2__ {int /*<<< orphan*/  mpt_bitmap; } ;
struct mlx4_priv {TYPE_1__ mr_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_bitmap_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void __mlx4_mpt_release(struct mlx4_dev *dev, u32 index)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	mlx4_bitmap_free(&priv->mr_table.mpt_bitmap, index);
}