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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_EXPR ; 
 int /*<<< orphan*/  BUILT_IN_SQRT ; 
 scalar_t__ COMPLEX_CST ; 
 scalar_t__ COMPLEX_EXPR ; 
 scalar_t__ COMPLEX_TYPE ; 
 scalar_t__ CONJ_EXPR ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NEGATE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_IMAGPART (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_REALPART (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_real (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__ builtin_save_expr (scalar_t__) ; 
 int /*<<< orphan*/  flag_trapping_math ; 
 scalar_t__ flag_unsafe_math_optimizations ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mathfn_built_in (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  optimize_size ; 
 int /*<<< orphan*/  real_arithmetic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ real_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ real_zerop (scalar_t__) ; 

__attribute__((used)) static tree
fold_builtin_cabs (tree arglist, tree type, tree fndecl)
{
  tree arg;

  if (!arglist || TREE_CHAIN (arglist))
    return NULL_TREE;

  arg = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (arg)) != COMPLEX_TYPE
      || TREE_CODE (TREE_TYPE (TREE_TYPE (arg))) != REAL_TYPE)
    return NULL_TREE;

  /* Evaluate cabs of a constant at compile-time.  */
  if (flag_unsafe_math_optimizations
      && TREE_CODE (arg) == COMPLEX_CST
      && TREE_CODE (TREE_REALPART (arg)) == REAL_CST
      && TREE_CODE (TREE_IMAGPART (arg)) == REAL_CST
      && ! TREE_CONSTANT_OVERFLOW (TREE_REALPART (arg))
      && ! TREE_CONSTANT_OVERFLOW (TREE_IMAGPART (arg)))
    {
      REAL_VALUE_TYPE r, i;

      r = TREE_REAL_CST (TREE_REALPART (arg));
      i = TREE_REAL_CST (TREE_IMAGPART (arg));

      real_arithmetic (&r, MULT_EXPR, &r, &r);
      real_arithmetic (&i, MULT_EXPR, &i, &i);
      real_arithmetic (&r, PLUS_EXPR, &r, &i);
      if (real_sqrt (&r, TYPE_MODE (type), &r)
	  || ! flag_trapping_math)
	return build_real (type, r);
    }

  /* If either part is zero, cabs is fabs of the other.  */
  if (TREE_CODE (arg) == COMPLEX_EXPR
      && real_zerop (TREE_OPERAND (arg, 0)))
    return fold_build1 (ABS_EXPR, type, TREE_OPERAND (arg, 1));
  if (TREE_CODE (arg) == COMPLEX_EXPR
      && real_zerop (TREE_OPERAND (arg, 1)))
    return fold_build1 (ABS_EXPR, type, TREE_OPERAND (arg, 0));

  /* Optimize cabs(-z) and cabs(conj(z)) as cabs(z).  */
  if (TREE_CODE (arg) == NEGATE_EXPR
      || TREE_CODE (arg) == CONJ_EXPR)
    {
      tree arglist = build_tree_list (NULL_TREE, TREE_OPERAND (arg, 0));
      return build_function_call_expr (fndecl, arglist);
    }

  /* Don't do this when optimizing for size.  */
  if (flag_unsafe_math_optimizations
      && optimize && !optimize_size)
    {
      tree sqrtfn = mathfn_built_in (type, BUILT_IN_SQRT);

      if (sqrtfn != NULL_TREE)
	{
	  tree rpart, ipart, result, arglist;

	  arg = builtin_save_expr (arg);

	  rpart = fold_build1 (REALPART_EXPR, type, arg);
	  ipart = fold_build1 (IMAGPART_EXPR, type, arg);

	  rpart = builtin_save_expr (rpart);
	  ipart = builtin_save_expr (ipart);

	  result = fold_build2 (PLUS_EXPR, type,
				fold_build2 (MULT_EXPR, type,
					     rpart, rpart),
				fold_build2 (MULT_EXPR, type,
					     ipart, ipart));

	  arglist = build_tree_list (NULL_TREE, result);
	  return build_function_call_expr (sqrtfn, arglist);
	}
    }

  return NULL_TREE;
}