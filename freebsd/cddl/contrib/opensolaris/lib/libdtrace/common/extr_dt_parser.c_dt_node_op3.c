#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dn_kind; scalar_t__ dn_value; struct TYPE_7__* dn_right; struct TYPE_7__* dn_left; struct TYPE_7__* dn_expr; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 scalar_t__ DT_NODE_INT ; 
 int /*<<< orphan*/  DT_NODE_OP3 ; 
 int /*<<< orphan*/  DT_TOK_QUESTION ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 

dt_node_t *
dt_node_op3(dt_node_t *expr, dt_node_t *lp, dt_node_t *rp)
{
	dt_node_t *dnp;

	if (expr->dn_kind == DT_NODE_INT)
		return (expr->dn_value != 0 ? lp : rp);

	dnp = dt_node_alloc(DT_NODE_OP3);
	dnp->dn_op = DT_TOK_QUESTION;
	dnp->dn_expr = expr;
	dnp->dn_left = lp;
	dnp->dn_right = rp;

	return (dnp);
}