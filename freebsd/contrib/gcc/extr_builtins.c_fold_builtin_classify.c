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
#define  BUILT_IN_FINITE 130 
#define  BUILT_IN_ISINF 129 
#define  BUILT_IN_ISNAN 128 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  GT_EXPR ; 
 int /*<<< orphan*/  HONOR_INFINITIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HONOR_NANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int /*<<< orphan*/  UNORDERED_EXPR ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ builtin_save_expr (scalar_t__) ; 
 int /*<<< orphan*/  dconst0 ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_minus_one_node ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ omit_one_operand (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  real_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_isinf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_isnan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_classify (tree fndecl, tree arglist, int builtin_index)
{
  tree type = TREE_TYPE (TREE_TYPE (fndecl));
  tree arg;
  REAL_VALUE_TYPE r;

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    {
      /* Check that we have exactly one argument.  */
      if (arglist == 0)
	{
	  error ("too few arguments to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
	  return error_mark_node;
	}
      else if (TREE_CHAIN (arglist) != 0)
	{
	  error ("too many arguments to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
	  return error_mark_node;
	}
      else
	{
	  error ("non-floating-point argument to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
	  return error_mark_node;
	}
    }

  arg = TREE_VALUE (arglist);
  switch (builtin_index)
    {
    case BUILT_IN_ISINF:
      if (!HONOR_INFINITIES (TYPE_MODE (TREE_TYPE (arg))))
	return omit_one_operand (type, integer_zero_node, arg);

      if (TREE_CODE (arg) == REAL_CST)
	{
	  r = TREE_REAL_CST (arg);
	  if (real_isinf (&r))
	    return real_compare (GT_EXPR, &r, &dconst0)
		   ? integer_one_node : integer_minus_one_node;
	  else
	    return integer_zero_node;
	}

      return NULL_TREE;

    case BUILT_IN_FINITE:
      if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg)))
	  && !HONOR_INFINITIES (TYPE_MODE (TREE_TYPE (arg))))
	return omit_one_operand (type, integer_one_node, arg);

      if (TREE_CODE (arg) == REAL_CST)
	{
	  r = TREE_REAL_CST (arg);
	  return real_isinf (&r) || real_isnan (&r)
		 ? integer_zero_node : integer_one_node;
	}

      return NULL_TREE;

    case BUILT_IN_ISNAN:
      if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg))))
	return omit_one_operand (type, integer_zero_node, arg);

      if (TREE_CODE (arg) == REAL_CST)
	{
	  r = TREE_REAL_CST (arg);
	  return real_isnan (&r) ? integer_one_node : integer_zero_node;
	}

      arg = builtin_save_expr (arg);
      return fold_build2 (UNORDERED_EXPR, type, arg, arg);

    default:
      gcc_unreachable ();
    }
}