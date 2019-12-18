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
union ib_gid {int* raw; } ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct TYPE_2__ {int (* attach_mcast ) (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ; 

int ib_attach_mcast(struct ib_qp *qp, union ib_gid *gid, u16 lid)
{
	int ret;

	if (!qp->device->attach_mcast)
		return -ENOSYS;
	if (gid->raw[0] != 0xff || qp->qp_type != IB_QPT_UD)
		return -EINVAL;

	ret = qp->device->attach_mcast(qp, gid, lid);
	if (!ret)
		atomic_inc(&qp->usecnt);
	return ret;
}