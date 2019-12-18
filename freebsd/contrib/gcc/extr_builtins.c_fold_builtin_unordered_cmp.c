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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ HONOR_NANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int INTEGER_TYPE ; 
 scalar_t__ NULL_TREE ; 
 int REAL_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TRUTH_NOT_EXPR ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int UNORDERED_EXPR ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ omit_two_operands (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_unordered_cmp (tree fndecl, tree arglist,
			    enum tree_code unordered_code,
			    enum tree_code ordered_code)
{
  tree type = TREE_TYPE (TREE_TYPE (fndecl));
  enum tree_code code;
  tree arg0, arg1;
  tree type0, type1;
  enum tree_code code0, code1;
  tree cmp_type = NULL_TREE;

  if (!validate_arglist (arglist, REAL_TYPE, REAL_TYPE, VOID_TYPE))
    {
      /* Check that we have exactly two arguments.  */
      if (arglist == 0 || TREE_CHAIN (arglist) == 0)
	{
	  error ("too few arguments to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
	  return error_mark_node;
	}
      else if (TREE_CHAIN (TREE_CHAIN (arglist)) != 0)
	{
	  error ("too many arguments to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
	  return error_mark_node;
	}
    }

  arg0 = TREE_VALUE (arglist);
  arg1 = TREE_VALUE (TREE_CHAIN (arglist));

  type0 = TREE_TYPE (arg0);
  type1 = TREE_TYPE (arg1);

  code0 = TREE_CODE (type0);
  code1 = TREE_CODE (type1);

  if (code0 == REAL_TYPE && code1 == REAL_TYPE)
    /* Choose the wider of two real types.  */
    cmp_type = TYPE_PRECISION (type0) >= TYPE_PRECISION (type1)
      ? type0 : type1;
  else if (code0 == REAL_TYPE && code1 == INTEGER_TYPE)
    cmp_type = type0;
  else if (code0 == INTEGER_TYPE && code1 == REAL_TYPE)
    cmp_type = type1;
  else
    {
      error ("non-floating-point argument to function %qs",
		 IDENTIFIER_POINTER (DECL_NAME (fndecl)));
      return error_mark_node;
    }

  arg0 = fold_convert (cmp_type, arg0);
  arg1 = fold_convert (cmp_type, arg1);

  if (unordered_code == UNORDERED_EXPR)
    {
      if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg0))))
	return omit_two_operands (type, integer_zero_node, arg0, arg1);
      return fold_build2 (UNORDERED_EXPR, type, arg0, arg1);
    }

  code = HONOR_NANS (TYPE_MODE (TREE_TYPE (arg0))) ? unordered_code
						   : ordered_code;
  return fold_build1 (TRUTH_NOT_EXPR, type,
		      fold_build2 (code, type, arg0, arg1));
}