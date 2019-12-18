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
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int c2_qp_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  to_c2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_c2qp (struct ib_qp*) ; 

__attribute__((used)) static int c2_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
			int attr_mask, struct ib_udata *udata)
{
	int err;

	err =
	    c2_qp_modify(to_c2dev(ibqp->device), to_c2qp(ibqp), attr,
			 attr_mask);

	return err;
}