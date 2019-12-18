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
struct mlx4_srq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_srq_table srq_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int mlx4_bitmap_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bitmap_free (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_table_get (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx4_table_put (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 

int __mlx4_srq_alloc_icm(struct mlx4_dev *dev, int *srqn)
{
	struct mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	int err;


	*srqn = mlx4_bitmap_alloc(&srq_table->bitmap);
	if (*srqn == -1)
		return -ENOMEM;

	err = mlx4_table_get(dev, &srq_table->table, *srqn);
	if (err)
		goto err_out;

	err = mlx4_table_get(dev, &srq_table->cmpt_table, *srqn);
	if (err)
		goto err_put;
	return 0;

err_put:
	mlx4_table_put(dev, &srq_table->table, *srqn);

err_out:
	mlx4_bitmap_free(&srq_table->bitmap, *srqn);
	return err;
}