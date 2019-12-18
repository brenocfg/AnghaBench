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
struct mlx4_mr {int /*<<< orphan*/  key; scalar_t__ enabled; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_to_hw_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_mpt_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_mpt_release (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int mlx4_mr_free_reserved (struct mlx4_dev*,struct mlx4_mr*) ; 

int mlx4_mr_free(struct mlx4_dev *dev, struct mlx4_mr *mr)
{
	int ret;

	ret = mlx4_mr_free_reserved(dev, mr);
	if (ret)
		return ret;
	if (mr->enabled)
		mlx4_mpt_free_icm(dev, key_to_hw_index(mr->key));
	mlx4_mpt_release(dev, key_to_hw_index(mr->key));

	return 0;
}