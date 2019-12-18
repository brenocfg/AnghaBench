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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 int DECL_FUNCTION_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int builtin_mathfn_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_errno_math ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_valued_real_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mathfn_built_in (int /*<<< orphan*/ ,int) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  strip_float_extensions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_trunc_transparent_mathfn (tree fndecl, tree arglist)
{
  enum built_in_function fcode = DECL_FUNCTION_CODE (fndecl);
  tree arg;

  if (! validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  /* Integer rounding functions are idempotent.  */
  if (fcode == builtin_mathfn_code (arg))
    return arg;

  /* If argument is already integer valued, and we don't need to worry
     about setting errno, there's no need to perform rounding.  */
  if (! flag_errno_math && integer_valued_real_p (arg))
    return arg;

  if (optimize)
    {
      tree arg0 = strip_float_extensions (arg);
      tree ftype = TREE_TYPE (TREE_TYPE (fndecl));
      tree newtype = TREE_TYPE (arg0);
      tree decl;

      if (TYPE_PRECISION (newtype) < TYPE_PRECISION (ftype)
	  && (decl = mathfn_built_in (newtype, fcode)))
	{
	  arglist =
	    build_tree_list (NULL_TREE, fold_convert (newtype, arg0));
	  return fold_convert (ftype,
			       build_function_call_expr (decl, arglist));
	}
    }
  return 0;
}