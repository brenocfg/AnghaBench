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
typedef  scalar_t__ tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 int BUILT_IN_VAL_COMPARE_AND_SWAP_N ; 
 scalar_t__ CODE_FOR_nothing ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int GS_ALL_DONE ; 
 int GS_ERROR ; 
 int GS_UNHANDLED ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 size_t TYPE_MODE (scalar_t__) ; 
 int /*<<< orphan*/  VIEW_CONVERT_EXPR ; 
 scalar_t__ boolean_type_node ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ build_fold_indirect_ref (scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__* built_in_decls ; 
 scalar_t__ create_artificial_label () ; 
 scalar_t__ create_tmp_var (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gimplify_and_add (scalar_t__,scalar_t__*) ; 
 scalar_t__ goa_stabilize_expr (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 
 scalar_t__* sync_compare_and_swap ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static enum gimplify_status
gimplify_omp_atomic_pipeline (tree *expr_p, tree *pre_p, tree addr,
			      tree rhs, int index)
{
  tree oldval, oldival, oldival2, newval, newival, label;
  tree type, itype, cmpxchg, args, x, iaddr;

  cmpxchg = built_in_decls[BUILT_IN_VAL_COMPARE_AND_SWAP_N + index + 1];
  type = TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (addr)));
  itype = TREE_TYPE (TREE_TYPE (cmpxchg));

  if (sync_compare_and_swap[TYPE_MODE (itype)] == CODE_FOR_nothing)
    return GS_UNHANDLED;

  oldval = create_tmp_var (type, NULL);
  newval = create_tmp_var (type, NULL);

  /* Precompute as much of RHS as possible.  In the same walk, replace
     occurrences of the lhs value with our temporary.  */
  if (goa_stabilize_expr (&rhs, pre_p, addr, oldval) < 0)
    return GS_ERROR;

  x = build_fold_indirect_ref (addr);
  x = build2 (MODIFY_EXPR, void_type_node, oldval, x);
  gimplify_and_add (x, pre_p);

  /* For floating-point values, we'll need to view-convert them to integers
     so that we can perform the atomic compare and swap.  Simplify the 
     following code by always setting up the "i"ntegral variables.  */
  if (INTEGRAL_TYPE_P (type) || POINTER_TYPE_P (type))
    {
      oldival = oldval;
      newival = newval;
      iaddr = addr;
    }
  else
    {
      oldival = create_tmp_var (itype, NULL);
      newival = create_tmp_var (itype, NULL);

      x = build1 (VIEW_CONVERT_EXPR, itype, oldval);
      x = build2 (MODIFY_EXPR, void_type_node, oldival, x);
      gimplify_and_add (x, pre_p);
      iaddr = fold_convert (build_pointer_type (itype), addr);
    }

  oldival2 = create_tmp_var (itype, NULL);

  label = create_artificial_label ();
  x = build1 (LABEL_EXPR, void_type_node, label);
  gimplify_and_add (x, pre_p);

  x = build2 (MODIFY_EXPR, void_type_node, newval, rhs);
  gimplify_and_add (x, pre_p);

  if (newval != newival)
    {
      x = build1 (VIEW_CONVERT_EXPR, itype, newval);
      x = build2 (MODIFY_EXPR, void_type_node, newival, x);
      gimplify_and_add (x, pre_p);
    }

  x = build2 (MODIFY_EXPR, void_type_node, oldival2,
	      fold_convert (itype, oldival));
  gimplify_and_add (x, pre_p);

  args = tree_cons (NULL, fold_convert (itype, newival), NULL);
  args = tree_cons (NULL, fold_convert (itype, oldival), args);
  args = tree_cons (NULL, iaddr, args);
  x = build_function_call_expr (cmpxchg, args);
  if (oldval == oldival)
    x = fold_convert (type, x);
  x = build2 (MODIFY_EXPR, void_type_node, oldival, x);
  gimplify_and_add (x, pre_p);

  /* For floating point, be prepared for the loop backedge.  */
  if (oldval != oldival)
    {
      x = build1 (VIEW_CONVERT_EXPR, type, oldival);
      x = build2 (MODIFY_EXPR, void_type_node, oldval, x);
      gimplify_and_add (x, pre_p);
    }

  /* Note that we always perform the comparison as an integer, even for
     floating point.  This allows the atomic operation to properly 
     succeed even with NaNs and -0.0.  */
  x = build3 (COND_EXPR, void_type_node,
	      build2 (NE_EXPR, boolean_type_node, oldival, oldival2),
	      build1 (GOTO_EXPR, void_type_node, label), NULL);
  gimplify_and_add (x, pre_p);

  *expr_p = NULL;
  return GS_ALL_DONE;
}