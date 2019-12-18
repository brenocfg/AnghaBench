#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dtsp_pdescs; } ;
typedef  TYPE_1__ dt_sugar_parse_t ;
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_TOK_ASGN ; 
 int /*<<< orphan*/  DT_TOK_LAND ; 
 int /*<<< orphan*/  DT_TOK_LNEG ; 
 int /*<<< orphan*/ * dt_node_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_int (int) ; 
 int /*<<< orphan*/ * dt_node_op1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_node_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_sugar_new_condition_var (int) ; 
 int /*<<< orphan*/  dt_sugar_new_error_var () ; 

__attribute__((used)) static dt_node_t *
dt_sugar_new_condition_impl(dt_sugar_parse_t *dp,
    dt_node_t *pred, int condid, int newcond)
{
	dt_node_t *value, *body, *newpred;

	/* predicate is !self->%error */
	newpred = dt_node_op1(DT_TOK_LNEG, dt_sugar_new_error_var());

	if (condid == 0) {
		/*
		 * value is (1 && pred)
		 *
		 * Note, D doesn't allow a probe-local "this" variable to
		 * be reused as a different type, even from a different probe.
		 * Therefore, value can't simply be <pred>, because then
		 * its type could be different when we reuse this condid
		 * in a different meta-clause.
		 */
		value = dt_node_op2(DT_TOK_LAND, dt_node_int(1), pred);
	} else {
		/* value is (this->%condition_<condid> && pred) */
		value = dt_node_op2(DT_TOK_LAND,
		    dt_sugar_new_condition_var(condid), pred);
	}

	/* body is "this->%condition_<retval> = <value>;" */
	body = dt_node_statement(dt_node_op2(DT_TOK_ASGN,
	    dt_sugar_new_condition_var(newcond), value));

	return (dt_node_clause(dp->dtsp_pdescs, newpred, body));
}