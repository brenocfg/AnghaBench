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
struct mlx4_qp {int /*<<< orphan*/  qpn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void mlx4_qp_free(struct mlx4_dev *dev, struct mlx4_qp *qp)
{
	if (atomic_dec_and_test(&qp->refcount))
		complete(&qp->free);
	wait_for_completion(&qp->free);

	mlx4_qp_free_icm(dev, qp->qpn);
}