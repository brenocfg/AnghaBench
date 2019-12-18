#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  pd; } ;
struct qib_qp {TYPE_1__ ibqp; } ;
struct qib_ibport {int /*<<< orphan*/  qp0; } ;
struct ib_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid; } ;
struct ib_ah {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct ib_ah* ib_create_ah (int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  memset (struct ib_ah_attr*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ppd_from_ibp (struct qib_ibport*) ; 
 struct qib_qp* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct ib_ah *qib_create_qp0_ah(struct qib_ibport *ibp, u16 dlid)
{
	struct ib_ah_attr attr;
	struct ib_ah *ah = ERR_PTR(-EINVAL);
	struct qib_qp *qp0;

	memset(&attr, 0, sizeof attr);
	attr.dlid = dlid;
	attr.port_num = ppd_from_ibp(ibp)->port;
	rcu_read_lock();
	qp0 = rcu_dereference(ibp->qp0);
	if (qp0)
		ah = ib_create_ah(qp0->ibqp.pd, &attr);
	rcu_read_unlock();
	return ah;
}