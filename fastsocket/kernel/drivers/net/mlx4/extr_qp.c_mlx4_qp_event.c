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
struct mlx4_qp_table {int /*<<< orphan*/  lock; } ;
struct mlx4_qp {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  (* event ) (struct mlx4_qp*,int) ;} ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_qp_table qp_table; } ;

/* Variables and functions */
 struct mlx4_qp* __mlx4_qp_lookup (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx4_qp*,int) ; 

void mlx4_qp_event(struct mlx4_dev *dev, u32 qpn, int event_type)
{
	struct mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	struct mlx4_qp *qp;

	spin_lock(&qp_table->lock);

	qp = __mlx4_qp_lookup(dev, qpn);
	if (qp)
		atomic_inc(&qp->refcount);

	spin_unlock(&qp_table->lock);

	if (!qp) {
		mlx4_dbg(dev, "Async event for none existent QP %08x\n", qpn);
		return;
	}

	qp->event(qp, event_type);

	if (atomic_dec_and_test(&qp->refcount))
		complete(&qp->free);
}