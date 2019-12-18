#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ step; scalar_t__ base; } ;
struct tree_niter_desc {int cmp; int /*<<< orphan*/  may_be_zero; scalar_t__ bound; TYPE_1__ control; } ;
struct loop {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int ERROR_MARK ; 
 int GE_EXPR ; 
 int GT_EXPR ; 
 int LE_EXPR ; 
 int LT_EXPR ; 
 int MINUS_EXPR ; 
 int MULT_EXPR ; 
 int NE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int PLUS_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int TRUTH_AND_EXPR ; 
 scalar_t__ boolean_false_node ; 
 scalar_t__ boolean_true_node ; 
 scalar_t__ boolean_type_node ; 
 int /*<<< orphan*/  bsi_insert_on_edge_immediate_loop (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_int_cst_type (scalar_t__,unsigned int) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ force_gimple_operand (scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ invert_truthvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_condexpr (scalar_t__) ; 
 int /*<<< orphan*/  loop_preheader_edge (struct loop*) ; 
 scalar_t__ lower_bound_in_type (scalar_t__,scalar_t__) ; 
 int tree_int_cst_sign_bit (scalar_t__) ; 
 scalar_t__ unshare_expr (scalar_t__) ; 
 scalar_t__ upper_bound_in_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
determine_exit_conditions (struct loop *loop, struct tree_niter_desc *desc,
			   unsigned factor, tree *enter_cond,
			   tree *exit_base, tree *exit_step,
			   enum tree_code *exit_cmp, tree *exit_bound)
{
  tree stmts;
  tree base = desc->control.base;
  tree step = desc->control.step;
  tree bound = desc->bound;
  tree type = TREE_TYPE (base);
  tree bigstep, delta;
  tree min = lower_bound_in_type (type, type);
  tree max = upper_bound_in_type (type, type);
  enum tree_code cmp = desc->cmp;
  tree cond = boolean_true_node, assum;

  *enter_cond = boolean_false_node;
  *exit_base = NULL_TREE;
  *exit_step = NULL_TREE;
  *exit_cmp = ERROR_MARK;
  *exit_bound = NULL_TREE;
  gcc_assert (cmp != ERROR_MARK);

  /* We only need to be correct when we answer question
     "Do at least FACTOR more iterations remain?" in the unrolled loop.
     Thus, transforming BASE + STEP * i <> BOUND to
     BASE + STEP * i < BOUND is ok.  */
  if (cmp == NE_EXPR)
    {
      if (tree_int_cst_sign_bit (step))
	cmp = GT_EXPR;
      else
	cmp = LT_EXPR;
    }
  else if (cmp == LT_EXPR)
    {
      gcc_assert (!tree_int_cst_sign_bit (step));
    }
  else if (cmp == GT_EXPR)
    {
      gcc_assert (tree_int_cst_sign_bit (step));
    }
  else
    gcc_unreachable ();

  /* The main body of the loop may be entered iff:

     1) desc->may_be_zero is false.
     2) it is possible to check that there are at least FACTOR iterations
	of the loop, i.e., BOUND - step * FACTOR does not overflow.
     3) # of iterations is at least FACTOR  */

  if (!zero_p (desc->may_be_zero))
    cond = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
			invert_truthvalue (desc->may_be_zero),
			cond);

  bigstep = fold_build2 (MULT_EXPR, type, step,
			 build_int_cst_type (type, factor));
  delta = fold_build2 (MINUS_EXPR, type, bigstep, step);
  if (cmp == LT_EXPR)
    assum = fold_build2 (GE_EXPR, boolean_type_node,
			 bound,
			 fold_build2 (PLUS_EXPR, type, min, delta));
  else
    assum = fold_build2 (LE_EXPR, boolean_type_node,
			 bound,
			 fold_build2 (PLUS_EXPR, type, max, delta));
  cond = fold_build2 (TRUTH_AND_EXPR, boolean_type_node, assum, cond);

  bound = fold_build2 (MINUS_EXPR, type, bound, delta);
  assum = fold_build2 (cmp, boolean_type_node, base, bound);
  cond = fold_build2 (TRUTH_AND_EXPR, boolean_type_node, assum, cond);

  cond = force_gimple_operand (unshare_expr (cond), &stmts, false, NULL_TREE);
  if (stmts)
    bsi_insert_on_edge_immediate_loop (loop_preheader_edge (loop), stmts);
  /* cond now may be a gimple comparison, which would be OK, but also any
     other gimple rhs (say a && b).  In this case we need to force it to
     operand.  */
  if (!is_gimple_condexpr (cond))
    {
      cond = force_gimple_operand (cond, &stmts, true, NULL_TREE);
      if (stmts)
	bsi_insert_on_edge_immediate_loop (loop_preheader_edge (loop), stmts);
    }
  *enter_cond = cond;

  base = force_gimple_operand (unshare_expr (base), &stmts, true, NULL_TREE);
  if (stmts)
    bsi_insert_on_edge_immediate_loop (loop_preheader_edge (loop), stmts);
  bound = force_gimple_operand (unshare_expr (bound), &stmts, true, NULL_TREE);
  if (stmts)
    bsi_insert_on_edge_immediate_loop (loop_preheader_edge (loop), stmts);

  *exit_base = base;
  *exit_step = bigstep;
  *exit_cmp = cmp;
  *exit_bound = bound;
}