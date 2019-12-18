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
struct ipath_swqe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ipath_qp {int /*<<< orphan*/  timerwait; TYPE_1__ ibqp; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  s_sge; int /*<<< orphan*/  s_len; } ;
struct ipath_ibdev {size_t pending_index; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/ * pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_mtu_enum_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restart_sge (int /*<<< orphan*/ *,struct ipath_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipath_init_restart(struct ipath_qp *qp, struct ipath_swqe *wqe)
{
	struct ipath_ibdev *dev;

	qp->s_len = restart_sge(&qp->s_sge, wqe, qp->s_psn,
				ib_mtu_enum_to_int(qp->path_mtu));
	dev = to_idev(qp->ibqp.device);
	spin_lock(&dev->pending_lock);
	if (list_empty(&qp->timerwait))
		list_add_tail(&qp->timerwait,
			      &dev->pending[dev->pending_index]);
	spin_unlock(&dev->pending_lock);
}