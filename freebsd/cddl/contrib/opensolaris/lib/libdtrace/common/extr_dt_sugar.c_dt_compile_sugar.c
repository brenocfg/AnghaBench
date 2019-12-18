#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* dt_has_sugar; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_16__ {scalar_t__ dtsp_num_ifs; scalar_t__ dtsp_num_conditions; TYPE_3__* dtsp_clause_list; int /*<<< orphan*/  dtsp_pdescs; TYPE_1__* dtsp_dtp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ dt_sugar_parse_t ;
struct TYPE_17__ {int /*<<< orphan*/ * dn_list; int /*<<< orphan*/ * dn_acts; int /*<<< orphan*/ * dn_pred; int /*<<< orphan*/  dn_pdescs; } ;
typedef  TYPE_3__ dt_node_t ;

/* Variables and functions */
 void* B_TRUE ; 
 int /*<<< orphan*/  dt_node_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_sugar_append_clause (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_makeerrorclause () ; 
 int /*<<< orphan*/  dt_sugar_new_basic_block (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_sugar_new_clearerror_clause (TYPE_2__*) ; 
 int dt_sugar_new_condition (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_sugar_prepend_clause (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_visit_all (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_sugar_visit_stmts (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 void* yyintdecimal ; 
 scalar_t__ yyintprefix ; 
 char* yyintsuffix ; 

dt_node_t *
dt_compile_sugar(dtrace_hdl_t *dtp, dt_node_t *clause)
{
	dt_sugar_parse_t dp = { 0 };
	int condid = 0;

	dp.dtsp_dtp = dtp;
	dp.dtsp_pdescs = clause->dn_pdescs;

	/* make dt_node_int() generate an "int"-typed integer */
	yyintdecimal = B_TRUE;
	yyintsuffix[0] = '\0';
	yyintprefix = 0;

	dt_sugar_visit_all(&dp, clause);

	if (dp.dtsp_num_ifs == 0 && dp.dtsp_num_conditions == 0) {
		/*
		 * There is nothing that modifies the number of clauses.  Use
		 * the existing clause as-is, with its predicate intact.  This
		 * ensures that in the absence of D sugar, the body of the
		 * clause can create a variable that is referenced in the
		 * predicate.
		 */
		dt_sugar_append_clause(&dp, dt_node_clause(clause->dn_pdescs,
		    clause->dn_pred, clause->dn_acts));
	} else {
		if (clause->dn_pred != NULL) {
			condid = dt_sugar_new_condition(&dp,
			    clause->dn_pred, condid);
		}

		if (clause->dn_acts == NULL) {
			/*
			 * dt_sugar_visit_stmts() does not emit a clause with
			 * an empty body (e.g. if there's an empty "if" body),
			 * but we need the empty body here so that we
			 * continue to get the default tracing action.
			 */
			dt_sugar_new_basic_block(&dp, condid, NULL);
		} else {
			dt_sugar_visit_stmts(&dp, clause->dn_acts, condid);
		}
	}

	if (dp.dtsp_num_conditions != 0) {
		dt_sugar_prepend_clause(&dp,
		    dt_sugar_new_clearerror_clause(&dp));
	}

	if (dp.dtsp_clause_list != NULL &&
	    dp.dtsp_clause_list->dn_list != NULL && !dtp->dt_has_sugar) {
		dtp->dt_has_sugar = B_TRUE;
		dt_sugar_prepend_clause(&dp, dt_sugar_makeerrorclause());
	}
	return (dp.dtsp_clause_list);
}