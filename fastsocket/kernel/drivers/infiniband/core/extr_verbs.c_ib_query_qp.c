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
struct ib_qp_init_attr {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; TYPE_1__* device; } ;
struct TYPE_2__ {int (* query_qp ) (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ; 

int ib_query_qp(struct ib_qp *qp,
		struct ib_qp_attr *qp_attr,
		int qp_attr_mask,
		struct ib_qp_init_attr *qp_init_attr)
{
	return qp->device->query_qp ?
		qp->device->query_qp(qp->real_qp, qp_attr, qp_attr_mask, qp_init_attr) :
		-ENOSYS;
}