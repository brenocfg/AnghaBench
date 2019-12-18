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

/* Variables and functions */
 scalar_t__ CONTAINS_PLACEHOLDER_P (scalar_t__) ; 
 scalar_t__ EXPR_HAS_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/  EXPR_LOCUS (scalar_t__) ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_IS_SIZETYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ create_tmp_var (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_rvalue ; 
 int /*<<< orphan*/  gimplify_and_add (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gimplify_expr (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  is_gimple_val ; 
 scalar_t__ unshare_expr (scalar_t__) ; 

void
gimplify_one_sizepos (tree *expr_p, tree *stmt_p)
{
  tree type, expr = *expr_p;

  /* We don't do anything if the value isn't there, is constant, or contains
     A PLACEHOLDER_EXPR.  We also don't want to do anything if it's already
     a VAR_DECL.  If it's a VAR_DECL from another function, the gimplifier
     will want to replace it with a new variable, but that will cause problems
     if this type is from outside the function.  It's OK to have that here.  */
  if (expr == NULL_TREE || TREE_CONSTANT (expr)
      || TREE_CODE (expr) == VAR_DECL
      || CONTAINS_PLACEHOLDER_P (expr))
    return;

  type = TREE_TYPE (expr);
  *expr_p = unshare_expr (expr);

  gimplify_expr (expr_p, stmt_p, NULL, is_gimple_val, fb_rvalue);
  expr = *expr_p;

  /* Verify that we've an exact type match with the original expression.
     In particular, we do not wish to drop a "sizetype" in favour of a
     type of similar dimensions.  We don't want to pollute the generic
     type-stripping code with this knowledge because it doesn't matter
     for the bulk of GENERIC/GIMPLE.  It only matters that TYPE_SIZE_UNIT
     and friends retain their "sizetype-ness".  */
  if (TREE_TYPE (expr) != type
      && TREE_CODE (type) == INTEGER_TYPE
      && TYPE_IS_SIZETYPE (type))
    {
      tree tmp;

      *expr_p = create_tmp_var (type, NULL);
      tmp = build1 (NOP_EXPR, type, expr);
      tmp = build2 (MODIFY_EXPR, type, *expr_p, tmp);
      if (EXPR_HAS_LOCATION (expr))
	SET_EXPR_LOCUS (tmp, EXPR_LOCUS (expr));
      else
	SET_EXPR_LOCATION (tmp, input_location);

      gimplify_and_add (tmp, stmt_p);
    }
}