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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ POWI_MAX_MULTS ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  expand_builtin_mathfn_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_powi (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optimize_size ; 
 scalar_t__ powi_cost (int) ; 
 int /*<<< orphan*/  real_from_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ real_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int real_to_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_pow (tree exp, rtx target, rtx subtarget)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree arg0, arg1;

  if (! validate_arglist (arglist, REAL_TYPE, REAL_TYPE, VOID_TYPE))
    return 0;

  arg0 = TREE_VALUE (arglist);
  arg1 = TREE_VALUE (TREE_CHAIN (arglist));

  if (TREE_CODE (arg1) == REAL_CST
      && ! TREE_CONSTANT_OVERFLOW (arg1))
    {
      REAL_VALUE_TYPE cint;
      REAL_VALUE_TYPE c;
      HOST_WIDE_INT n;

      c = TREE_REAL_CST (arg1);
      n = real_to_integer (&c);
      real_from_integer (&cint, VOIDmode, n, n < 0 ? -1 : 0, 0);
      if (real_identical (&c, &cint))
	{
	  /* If the exponent is -1, 0, 1 or 2, then expand_powi is exact.
	     Otherwise, check the number of multiplications required.
	     Note that pow never sets errno for an integer exponent.  */
	  if ((n >= -1 && n <= 2)
	      || (flag_unsafe_math_optimizations
		  && ! optimize_size
		  && powi_cost (n) <= POWI_MAX_MULTS))
	    {
	      enum machine_mode mode = TYPE_MODE (TREE_TYPE (exp));
	      rtx op = expand_expr (arg0, subtarget, VOIDmode, 0);
	      op = force_reg (mode, op);
	      return expand_powi (op, mode, n);
	    }
	}
    }

  if (! flag_unsafe_math_optimizations)
    return NULL_RTX;
  return expand_builtin_mathfn_2 (exp, target, subtarget);
}