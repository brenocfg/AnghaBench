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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  REAL_VALUE_ISNAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_errno_math ; 
 int /*<<< orphan*/  fold_trunc_transparent_mathfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_floor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_floor (tree fndecl, tree arglist)
{
  tree arg;

  if (! validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;

  /* Optimize floor of constant value.  */
  arg = TREE_VALUE (arglist);
  if (TREE_CODE (arg) == REAL_CST && ! TREE_CONSTANT_OVERFLOW (arg))
    {
      REAL_VALUE_TYPE x;

      x = TREE_REAL_CST (arg);
      if (! REAL_VALUE_ISNAN (x) || ! flag_errno_math)
	{
	  tree type = TREE_TYPE (TREE_TYPE (fndecl));
	  REAL_VALUE_TYPE r;

	  real_floor (&r, TYPE_MODE (type), &x);
	  return build_real (type, r);
	}
    }

  return fold_trunc_transparent_mathfn (fndecl, arglist);
}