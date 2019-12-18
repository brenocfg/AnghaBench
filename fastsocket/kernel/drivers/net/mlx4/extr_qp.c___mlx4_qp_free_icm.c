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
struct mlx4_qp_table {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  auxc_table; int /*<<< orphan*/  altc_table; int /*<<< orphan*/  rdmarc_table; int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_table_put (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 

void __mlx4_qp_free_icm(struct mlx4_dev *dev, int qpn)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;

	mlx4_table_put(dev, &qp_table->cmpt_table, qpn);
	mlx4_table_put(dev, &qp_table->rdmarc_table, qpn);
	mlx4_table_put(dev, &qp_table->altc_table, qpn);
	mlx4_table_put(dev, &qp_table->auxc_table, qpn);
	mlx4_table_put(dev, &qp_table->qp_table, qpn);
}