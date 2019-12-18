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
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ CONVERT_EXPR ; 
 int EQ_EXPR ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ HAVE_canonicalize_funcptr_for_compare ; 
 scalar_t__ INTEGER_CST ; 
 int NE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_fit_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_sign_changed_comparison (enum tree_code code, tree type,
			      tree arg0, tree arg1)
{
  tree arg0_inner, tmp;
  tree inner_type, outer_type;

  if (TREE_CODE (arg0) != NOP_EXPR
      && TREE_CODE (arg0) != CONVERT_EXPR)
    return NULL_TREE;

  outer_type = TREE_TYPE (arg0);
  arg0_inner = TREE_OPERAND (arg0, 0);
  inner_type = TREE_TYPE (arg0_inner);

#ifdef HAVE_canonicalize_funcptr_for_compare
  /* Disable this optimization if we're casting a function pointer
     type on targets that require function pointer canonicalization.  */
  if (HAVE_canonicalize_funcptr_for_compare
      && TREE_CODE (inner_type) == POINTER_TYPE
      && TREE_CODE (TREE_TYPE (inner_type)) == FUNCTION_TYPE)
    return NULL_TREE;
#endif

  if (TYPE_PRECISION (inner_type) != TYPE_PRECISION (outer_type))
    return NULL_TREE;

  if (TREE_CODE (arg1) != INTEGER_CST
      && !((TREE_CODE (arg1) == NOP_EXPR
	    || TREE_CODE (arg1) == CONVERT_EXPR)
	   && TREE_TYPE (TREE_OPERAND (arg1, 0)) == inner_type))
    return NULL_TREE;

  if (TYPE_UNSIGNED (inner_type) != TYPE_UNSIGNED (outer_type)
      && code != NE_EXPR
      && code != EQ_EXPR)
    return NULL_TREE;

  if (TREE_CODE (arg1) == INTEGER_CST)
    {
      tmp = build_int_cst_wide (inner_type,
				TREE_INT_CST_LOW (arg1),
				TREE_INT_CST_HIGH (arg1));
      arg1 = force_fit_type (tmp, 0,
			     TREE_OVERFLOW (arg1),
			     TREE_CONSTANT_OVERFLOW (arg1));
    }
  else
    arg1 = fold_convert (inner_type, arg1);

  return fold_build2 (code, type, arg0_inner, arg1);
}