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
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_TOK_ASGN ; 
 int /*<<< orphan*/ * dt_node_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_int (int) ; 
 int /*<<< orphan*/  dt_node_op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_pdesc_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_statement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_new_error_var () ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static dt_node_t *
dt_sugar_makeerrorclause(void)
{
	dt_node_t *acts, *pdesc;

	pdesc = dt_node_pdesc_by_name(strdup("dtrace:::ERROR"));

	acts = dt_node_statement(dt_node_op2(DT_TOK_ASGN,
	    dt_sugar_new_error_var(), dt_node_int(1)));

	return (dt_node_clause(pdesc, NULL, acts));
}