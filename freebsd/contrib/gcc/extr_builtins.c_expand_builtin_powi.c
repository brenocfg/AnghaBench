#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {int /*<<< orphan*/  libfunc; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  INT_TYPE_SIZE ; 
 int /*<<< orphan*/  LCT_CONST_MAKE_BLOCK ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ POWI_MAX_MULTS ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  convert_to_mode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_powi (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int mode_for_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optimize_size ; 
 scalar_t__ powi_cost (int) ; 
 TYPE_2__* powi_optab ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_powi (tree exp, rtx target, rtx subtarget)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree arg0, arg1;
  rtx op0, op1;
  enum machine_mode mode;
  enum machine_mode mode2;

  if (! validate_arglist (arglist, REAL_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;

  arg0 = TREE_VALUE (arglist);
  arg1 = TREE_VALUE (TREE_CHAIN (arglist));
  mode = TYPE_MODE (TREE_TYPE (exp));

  /* Handle constant power.  */

  if (TREE_CODE (arg1) == INTEGER_CST
      && ! TREE_CONSTANT_OVERFLOW (arg1))
    {
      HOST_WIDE_INT n = TREE_INT_CST_LOW (arg1);

      /* If the exponent is -1, 0, 1 or 2, then expand_powi is exact.
	 Otherwise, check the number of multiplications required.  */
      if ((TREE_INT_CST_HIGH (arg1) == 0
	   || TREE_INT_CST_HIGH (arg1) == -1)
	  && ((n >= -1 && n <= 2)
	      || (! optimize_size
		  && powi_cost (n) <= POWI_MAX_MULTS)))
	{
	  op0 = expand_expr (arg0, subtarget, VOIDmode, 0);
	  op0 = force_reg (mode, op0);
	  return expand_powi (op0, mode, n);
	}
    }

  /* Emit a libcall to libgcc.  */

  /* Mode of the 2nd argument must match that of an int. */
  mode2 = mode_for_size (INT_TYPE_SIZE, MODE_INT, 0);

  if (target == NULL_RTX)
    target = gen_reg_rtx (mode);

  op0 = expand_expr (arg0, subtarget, mode, 0);
  if (GET_MODE (op0) != mode)
    op0 = convert_to_mode (mode, op0, 0);
  op1 = expand_expr (arg1, 0, mode2, 0);
  if (GET_MODE (op1) != mode2)
    op1 = convert_to_mode (mode2, op1, 0);

  target = emit_library_call_value (powi_optab->handlers[(int) mode].libfunc,
				    target, LCT_CONST_MAKE_BLOCK, mode, 2,
				    op0, mode, op1, mode2);

  return target;
}