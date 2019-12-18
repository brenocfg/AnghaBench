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
typedef  int /*<<< orphan*/ * tree ;
struct omp_for_data {int cond_code; int /*<<< orphan*/  v; int /*<<< orphan*/ * n2; int /*<<< orphan*/ * n1; int /*<<< orphan*/  for_stmt; int /*<<< orphan*/ * step; } ;
struct omp_context {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int EQ_EXPR ; 
 int GE_EXPR ; 
 int LE_EXPR ; 
 int LT_EXPR ; 
 int MODIFY_EXPR ; 
 int /*<<< orphan*/ * OMP_FOR_CLAUSES (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/ * build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lower_lastprivate_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,struct omp_context*) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_omp_for_lastprivate (struct omp_for_data *fd, tree *body_p,
			   tree *dlist, struct omp_context *ctx)
{
  tree clauses, cond, stmts, vinit, t;
  enum tree_code cond_code;
  
  cond_code = fd->cond_code;
  cond_code = cond_code == LT_EXPR ? GE_EXPR : LE_EXPR;

  /* When possible, use a strict equality expression.  This can let VRP
     type optimizations deduce the value and remove a copy.  */
  if (host_integerp (fd->step, 0))
    {
      HOST_WIDE_INT step = TREE_INT_CST_LOW (fd->step);
      if (step == 1 || step == -1)
	cond_code = EQ_EXPR;
    }

  cond = build2 (cond_code, boolean_type_node, fd->v, fd->n2);

  clauses = OMP_FOR_CLAUSES (fd->for_stmt);
  stmts = NULL;
  lower_lastprivate_clauses (clauses, cond, &stmts, ctx);
  if (stmts != NULL)
    {
      append_to_statement_list (stmts, dlist);

      /* Optimize: v = 0; is usually cheaper than v = some_other_constant.  */
      vinit = fd->n1;
      if (cond_code == EQ_EXPR
	  && host_integerp (fd->n2, 0)
	  && ! integer_zerop (fd->n2))
	vinit = build_int_cst (TREE_TYPE (fd->v), 0);

      /* Initialize the iterator variable, so that threads that don't execute
	 any iterations don't execute the lastprivate clauses by accident.  */
      t = build2 (MODIFY_EXPR, void_type_node, fd->v, vinit);
      gimplify_and_add (t, body_p);
    }
}