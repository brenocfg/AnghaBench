#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {TYPE_1__* handlers; } ;
struct TYPE_7__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS ; 
 int BRANCH_COST ; 
 scalar_t__ CODE_FOR_nothing ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int /*<<< orphan*/  HONOR_SIGNED_ZEROS (int) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 int /*<<< orphan*/  abs_optab ; 
 int /*<<< orphan*/  absv_optab ; 
 int /*<<< orphan*/  delete_insns_since (scalar_t__) ; 
 scalar_t__ expand_absneg_bit (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__ expand_binop (int,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_shift (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_unop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_trapv ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  neg_optab ; 
 int /*<<< orphan*/  size_int (scalar_t__) ; 
 TYPE_2__* smax_optab ; 
 TYPE_2__* sub_optab ; 
 TYPE_2__* subv_optab ; 
 TYPE_2__* xor_optab ; 

rtx
expand_abs_nojump (enum machine_mode mode, rtx op0, rtx target,
		   int result_unsignedp)
{
  rtx temp;

  if (! flag_trapv)
    result_unsignedp = 1;

  /* First try to do it with a special abs instruction.  */
  temp = expand_unop (mode, result_unsignedp ? abs_optab : absv_optab,
                      op0, target, 0);
  if (temp != 0)
    return temp;

  /* For floating point modes, try clearing the sign bit.  */
  if (SCALAR_FLOAT_MODE_P (mode))
    {
      temp = expand_absneg_bit (ABS, mode, op0, target);
      if (temp)
	return temp;
    }

  /* If we have a MAX insn, we can do this as MAX (x, -x).  */
  if (smax_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing
      && !HONOR_SIGNED_ZEROS (mode))
    {
      rtx last = get_last_insn ();

      temp = expand_unop (mode, neg_optab, op0, NULL_RTX, 0);
      if (temp != 0)
	temp = expand_binop (mode, smax_optab, op0, temp, target, 0,
			     OPTAB_WIDEN);

      if (temp != 0)
	return temp;

      delete_insns_since (last);
    }

  /* If this machine has expensive jumps, we can do integer absolute
     value of X as (((signed) x >> (W-1)) ^ x) - ((signed) x >> (W-1)),
     where W is the width of MODE.  */

  if (GET_MODE_CLASS (mode) == MODE_INT && BRANCH_COST >= 2)
    {
      rtx extended = expand_shift (RSHIFT_EXPR, mode, op0,
				   size_int (GET_MODE_BITSIZE (mode) - 1),
				   NULL_RTX, 0);

      temp = expand_binop (mode, xor_optab, extended, op0, target, 0,
			   OPTAB_LIB_WIDEN);
      if (temp != 0)
	temp = expand_binop (mode, result_unsignedp ? sub_optab : subv_optab,
                             temp, extended, target, 0, OPTAB_LIB_WIDEN);

      if (temp != 0)
	return temp;
    }

  return NULL_RTX;
}