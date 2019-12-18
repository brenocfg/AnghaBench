#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dt_sugar_parse_t ;
struct TYPE_5__ {scalar_t__ dn_kind; int /*<<< orphan*/ * dn_alternate_body; int /*<<< orphan*/ * dn_body; struct TYPE_5__* dn_conditional; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 scalar_t__ DT_NODE_IF ; 
 int /*<<< orphan*/  DT_TOK_LNEG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dt_node_op1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dt_sugar_new_condition (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dt_sugar_new_condition_var (int) ; 
 int /*<<< orphan*/  dt_sugar_visit_stmts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dt_sugar_do_if(dt_sugar_parse_t *dp, dt_node_t *if_stmt, int precondition)
{
	int newid;

	assert(if_stmt->dn_kind == DT_NODE_IF);

	/* condition */
	newid = dt_sugar_new_condition(dp,
	    if_stmt->dn_conditional, precondition);

	/* body of if */
	dt_sugar_visit_stmts(dp, if_stmt->dn_body, newid);

	/*
	 * Visit the body of the "else" statement, if present.  Note that we
	 * generate a new condition which is the inverse of the previous
	 * condition.
	 */
	if (if_stmt->dn_alternate_body != NULL) {
		dt_node_t *pred =
		    dt_node_op1(DT_TOK_LNEG, dt_sugar_new_condition_var(newid));
		dt_sugar_visit_stmts(dp, if_stmt->dn_alternate_body,
		    dt_sugar_new_condition(dp, pred, precondition));
	}
}