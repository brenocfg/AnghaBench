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
struct mlx4_qp_table {int /*<<< orphan*/  bitmap; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int mlx4_bitmap_alloc_range (int /*<<< orphan*/ *,int,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int __mlx4_qp_reserve_range(struct mlx4_dev *dev, int cnt, int align,
				   int *base)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;

	*base = mlx4_bitmap_alloc_range(&qp_table->bitmap, cnt, align);
	if (*base == -1)
		return -ENOMEM;

	return 0;
}