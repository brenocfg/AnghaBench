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
struct mlx4_qp_table {int /*<<< orphan*/  lock; } ;
struct mlx4_qp {int qpn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct TYPE_2__ {int num_qps; } ;
struct mlx4_dev {TYPE_1__ caps; int /*<<< orphan*/  qp_table_tree; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_qp_alloc_icm (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_qp_free_icm (struct mlx4_dev*,int) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct mlx4_qp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int mlx4_qp_alloc(struct mlx4_dev *dev, int qpn, struct mlx4_qp *qp)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;
	int err;

	if (!qpn)
		return -EINVAL;

	qp->qpn = qpn;

	err = mlx4_qp_alloc_icm(dev, qpn);
	if (err)
		return err;

	spin_lock_irq(&qp_table->lock);
	err = radix_tree_insert(&dev->qp_table_tree, qp->qpn &
				(dev->caps.num_qps - 1), qp);
	spin_unlock_irq(&qp_table->lock);
	if (err)
		goto err_icm;

	atomic_set(&qp->refcount, 1);
	init_completion(&qp->free);

	return 0;

err_icm:
	mlx4_qp_free_icm(dev, qpn);
	return err;
}