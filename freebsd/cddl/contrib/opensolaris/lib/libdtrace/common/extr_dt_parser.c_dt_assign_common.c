#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dn_op; scalar_t__ dn_kind; int dn_flags; int /*<<< orphan*/  dn_attr; struct TYPE_8__* dn_right; struct TYPE_8__* dn_left; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int DT_NF_LVALUE ; 
 int DT_NF_WRITABLE ; 
 scalar_t__ DT_NODE_INT ; 
 int /*<<< orphan*/  D_OP_LVAL ; 
 int /*<<< orphan*/  D_OP_WRITE ; 
 int /*<<< orphan*/  dt_attr_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cast (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_node_attr_assign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_propagate (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  opstr (int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_assign_common(dt_node_t *dnp)
{
	dt_node_t *lp = dnp->dn_left;
	dt_node_t *rp = dnp->dn_right;
	int op = dnp->dn_op;

	if (rp->dn_kind == DT_NODE_INT)
		dt_cast(lp, rp);

	if (!(lp->dn_flags & DT_NF_LVALUE)) {
		xyerror(D_OP_LVAL, "operator %s requires modifiable "
		    "lvalue as an operand\n", opstr(op));
		/* see K&R[A7.17] */
	}

	if (!(lp->dn_flags & DT_NF_WRITABLE)) {
		xyerror(D_OP_WRITE, "operator %s can only be applied "
		    "to a writable variable\n", opstr(op));
	}

	dt_node_type_propagate(lp, dnp); /* see K&R[A7.17] */
	dt_node_attr_assign(dnp, dt_attr_min(lp->dn_attr, rp->dn_attr));
}