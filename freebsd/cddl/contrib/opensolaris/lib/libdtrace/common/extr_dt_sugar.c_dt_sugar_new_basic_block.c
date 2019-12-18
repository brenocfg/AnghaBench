#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dtsp_num_conditions; int /*<<< orphan*/  dtsp_pdescs; } ;
typedef  TYPE_1__ dt_sugar_parse_t ;
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_TOK_LAND ; 
 int /*<<< orphan*/  DT_TOK_LNEG ; 
 int /*<<< orphan*/  dt_node_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_node_op1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_append_clause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_new_condition_var (int) ; 
 int /*<<< orphan*/  dt_sugar_new_error_var () ; 

__attribute__((used)) static void
dt_sugar_new_basic_block(dt_sugar_parse_t *dp, int condid, dt_node_t *stmts)
{
	dt_node_t *pred = NULL;

	if (condid == 0) {
		/*
		 * Don't bother with !error on the first clause, because if
		 * there is only one clause, we don't add the prelude to
		 * zero out %error.
		 */
		if (dp->dtsp_num_conditions != 0) {
			pred = dt_node_op1(DT_TOK_LNEG,
			    dt_sugar_new_error_var());
		}
	} else {
		pred = dt_node_op2(DT_TOK_LAND,
		    dt_node_op1(DT_TOK_LNEG, dt_sugar_new_error_var()),
		    dt_sugar_new_condition_var(condid));
	}
	dt_sugar_append_clause(dp,
	    dt_node_clause(dp->dtsp_pdescs, pred, stmts));
}