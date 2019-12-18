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
struct mlx4_mr_table {int /*<<< orphan*/  dmpt_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_mr_table mr_table; } ;

/* Variables and functions */
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_table_get (struct mlx4_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __mlx4_mpt_alloc_icm(struct mlx4_dev *dev, u32 index)
{
	struct mlx4_mr_table *mr_table = &mlx4_priv(dev)->mr_table;

	return mlx4_table_get(dev, &mr_table->dmpt_table, index);
}