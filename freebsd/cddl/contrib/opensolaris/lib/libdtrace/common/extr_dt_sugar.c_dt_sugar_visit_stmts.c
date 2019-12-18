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
struct TYPE_5__ {scalar_t__ dn_kind; struct TYPE_5__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 scalar_t__ DT_NODE_IF ; 
 int /*<<< orphan*/  dt_sugar_do_if (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dt_sugar_new_basic_block (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static void
dt_sugar_visit_stmts(dt_sugar_parse_t *dp, dt_node_t *stmts, int precondition)
{
	dt_node_t *stmt;
	dt_node_t *prev_stmt = NULL;
	dt_node_t *next_stmt;
	dt_node_t *first_stmt_in_basic_block = NULL;

	for (stmt = stmts; stmt != NULL; stmt = next_stmt) {
		next_stmt = stmt->dn_list;

		if (stmt->dn_kind != DT_NODE_IF) {
			if (first_stmt_in_basic_block == NULL)
				first_stmt_in_basic_block = stmt;
			prev_stmt = stmt;
			continue;
		}

		/*
		 * Remove this and following statements from the previous
		 * clause.
		 */
		if (prev_stmt != NULL)
			prev_stmt->dn_list = NULL;

		/*
		 * Generate clause for statements preceding the "if"
		 */
		if (first_stmt_in_basic_block != NULL) {
			dt_sugar_new_basic_block(dp, precondition,
			    first_stmt_in_basic_block);
		}

		dt_sugar_do_if(dp, stmt, precondition);

		first_stmt_in_basic_block = NULL;

		prev_stmt = stmt;
	}

	/* generate clause for statements after last "if". */
	if (first_stmt_in_basic_block != NULL) {
		dt_sugar_new_basic_block(dp, precondition,
		    first_stmt_in_basic_block);
	}
}