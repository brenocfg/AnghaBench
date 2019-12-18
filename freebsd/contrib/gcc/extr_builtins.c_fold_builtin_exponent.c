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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int const BUILT_IN_LOG ; 
 int const BUILT_IN_LOG10 ; 
 int const BUILT_IN_LOG10F ; 
 int const BUILT_IN_LOG10L ; 
 int const BUILT_IN_LOG2 ; 
 int const BUILT_IN_LOG2F ; 
 int const BUILT_IN_LOG2L ; 
 int const BUILT_IN_LOGF ; 
 int const BUILT_IN_LOGL ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int builtin_mathfn_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst1 ; 
 int /*<<< orphan*/  const dconst10 ; 
 int /*<<< orphan*/  const dconst2 ; 
 int /*<<< orphan*/  const dconste ; 
 scalar_t__ flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  real_from_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ real_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ real_onep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_powi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ real_to_integer (int /*<<< orphan*/ *) ; 
 scalar_t__ real_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__ validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_exponent (tree fndecl, tree arglist,
		       const REAL_VALUE_TYPE *value)
{
  if (validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    {
      tree type = TREE_TYPE (TREE_TYPE (fndecl));
      tree arg = TREE_VALUE (arglist);

      /* Optimize exp*(0.0) = 1.0.  */
      if (real_zerop (arg))
	return build_real (type, dconst1);

      /* Optimize expN(1.0) = N.  */
      if (real_onep (arg))
	{
	  REAL_VALUE_TYPE cst;

	  real_convert (&cst, TYPE_MODE (type), value);
	  return build_real (type, cst);
	}

      /* Attempt to evaluate expN(integer) at compile-time.  */
      if (flag_unsafe_math_optimizations
	  && TREE_CODE (arg) == REAL_CST
	  && ! TREE_CONSTANT_OVERFLOW (arg))
	{
	  REAL_VALUE_TYPE cint;
	  REAL_VALUE_TYPE c;
	  HOST_WIDE_INT n;

	  c = TREE_REAL_CST (arg);
	  n = real_to_integer (&c);
	  real_from_integer (&cint, VOIDmode, n,
			     n < 0 ? -1 : 0, 0);
	  if (real_identical (&c, &cint))
	    {
	      REAL_VALUE_TYPE x;

	      real_powi (&x, TYPE_MODE (type), value, n);
	      return build_real (type, x);
	    }
	}

      /* Optimize expN(logN(x)) = x.  */
      if (flag_unsafe_math_optimizations)
	{
	  const enum built_in_function fcode = builtin_mathfn_code (arg);

	  if ((value == &dconste
	       && (fcode == BUILT_IN_LOG
		   || fcode == BUILT_IN_LOGF
		   || fcode == BUILT_IN_LOGL))
	      || (value == &dconst2
		  && (fcode == BUILT_IN_LOG2
		      || fcode == BUILT_IN_LOG2F
		      || fcode == BUILT_IN_LOG2L))
	      || (value == &dconst10
		  && (fcode == BUILT_IN_LOG10
		      || fcode == BUILT_IN_LOG10F
		      || fcode == BUILT_IN_LOG10L)))
	    return fold_convert (type, TREE_VALUE (TREE_OPERAND (arg, 1)));
	}
    }

  return 0;
}