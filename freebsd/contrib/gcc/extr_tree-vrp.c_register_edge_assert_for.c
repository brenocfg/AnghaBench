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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ COND_EXPR_COND (scalar_t__) ; 
 int EDGE_FALSE_VALUE ; 
 int EQ_EXPR ; 
 int GT_EXPR ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int LT_EXPR ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ boolean_false_node ; 
 scalar_t__ boolean_true_node ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_values (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  found_in_subgraph ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int invert_tree_comparison (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_new_assert_for (scalar_t__,int,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int swap_tree_comparison (scalar_t__) ; 

__attribute__((used)) static bool
register_edge_assert_for (tree name, edge e, block_stmt_iterator si)
{
  tree val, stmt;
  enum tree_code comp_code;

  stmt = bsi_stmt (si);

  /* Do not attempt to infer anything in names that flow through
     abnormal edges.  */
  if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (name))
    return false;

  /* If NAME was not found in the sub-graph reachable from E, then
     there's nothing to do.  */
  if (!TEST_BIT (found_in_subgraph, SSA_NAME_VERSION (name)))
    return false;

  /* We found a use of NAME in the sub-graph rooted at E->DEST.
     Register an assertion for NAME according to the value that NAME
     takes on edge E.  */
  if (TREE_CODE (stmt) == COND_EXPR)
    {
      /* If BB ends in a COND_EXPR then NAME then we should insert
	 the original predicate on EDGE_TRUE_VALUE and the
	 opposite predicate on EDGE_FALSE_VALUE.  */
      tree cond = COND_EXPR_COND (stmt);
      bool is_else_edge = (e->flags & EDGE_FALSE_VALUE) != 0;

      /* Predicates may be a single SSA name or NAME OP VAL.  */
      if (cond == name)
	{
	  /* If the predicate is a name, it must be NAME, in which
	     case we create the predicate NAME == true or
	     NAME == false accordingly.  */
	  comp_code = EQ_EXPR;
	  val = (is_else_edge) ? boolean_false_node : boolean_true_node;
	}
      else
	{
	  /* Otherwise, we have a comparison of the form NAME COMP VAL
	     or VAL COMP NAME.  */
	  if (name == TREE_OPERAND (cond, 1))
	    {
	      /* If the predicate is of the form VAL COMP NAME, flip
		 COMP around because we need to register NAME as the
		 first operand in the predicate.  */
	      comp_code = swap_tree_comparison (TREE_CODE (cond));
	      val = TREE_OPERAND (cond, 0);
	    }
	  else
	    {
	      /* The comparison is of the form NAME COMP VAL, so the
		 comparison code remains unchanged.  */
	      comp_code = TREE_CODE (cond);
	      val = TREE_OPERAND (cond, 1);
	    }

	  /* If we are inserting the assertion on the ELSE edge, we
	     need to invert the sign comparison.  */
	  if (is_else_edge)
	    comp_code = invert_tree_comparison (comp_code, 0);

	  /* Do not register always-false predicates.  FIXME, this
	     works around a limitation in fold() when dealing with
	     enumerations.  Given 'enum { N1, N2 } x;', fold will not
	     fold 'if (x > N2)' to 'if (0)'.  */
	  if ((comp_code == GT_EXPR || comp_code == LT_EXPR)
	      && (INTEGRAL_TYPE_P (TREE_TYPE (val))
		  || SCALAR_FLOAT_TYPE_P (TREE_TYPE (val))))
	    {
	      tree min = TYPE_MIN_VALUE (TREE_TYPE (val));
	      tree max = TYPE_MAX_VALUE (TREE_TYPE (val));

	      if (comp_code == GT_EXPR && compare_values (val, max) == 0)
		return false;

	      if (comp_code == LT_EXPR && compare_values (val, min) == 0)
		return false;
	    }
	}
    }
  else
    {
      /* FIXME.  Handle SWITCH_EXPR.  */
      gcc_unreachable ();
    }

  register_new_assert_for (name, comp_code, val, NULL, e, si);
  return true;
}