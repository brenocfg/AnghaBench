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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 scalar_t__ CONSTANT_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  LEGITIMATE_CONSTANT_P (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ compress_float_constant (scalar_t__,scalar_t__) ; 
 scalar_t__ emit_move_insn_1 (scalar_t__,scalar_t__) ; 
 scalar_t__ flag_force_addr ; 
 scalar_t__ force_const_mem (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memory_address_p (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  push_operand (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 scalar_t__ use_anchored_address (scalar_t__) ; 
 scalar_t__ validize_mem (scalar_t__) ; 

rtx
emit_move_insn (rtx x, rtx y)
{
  enum machine_mode mode = GET_MODE (x);
  rtx y_cst = NULL_RTX;
  rtx last_insn, set;

  gcc_assert (mode != BLKmode
	      && (GET_MODE (y) == mode || GET_MODE (y) == VOIDmode));

  if (CONSTANT_P (y))
    {
      if (optimize
	  && SCALAR_FLOAT_MODE_P (GET_MODE (x))
	  && (last_insn = compress_float_constant (x, y)))
	return last_insn;

      y_cst = y;

      if (!LEGITIMATE_CONSTANT_P (y))
	{
	  y = force_const_mem (mode, y);

	  /* If the target's cannot_force_const_mem prevented the spill,
	     assume that the target's move expanders will also take care
	     of the non-legitimate constant.  */
	  if (!y)
	    y = y_cst;
	  else
	    y = use_anchored_address (y);
	}
    }

  /* If X or Y are memory references, verify that their addresses are valid
     for the machine.  */
  if (MEM_P (x)
      && ((! memory_address_p (GET_MODE (x), XEXP (x, 0))
	   && ! push_operand (x, GET_MODE (x)))
	  || (flag_force_addr
	      && CONSTANT_ADDRESS_P (XEXP (x, 0)))))
    x = validize_mem (x);

  if (MEM_P (y)
      && (! memory_address_p (GET_MODE (y), XEXP (y, 0))
	  || (flag_force_addr
	      && CONSTANT_ADDRESS_P (XEXP (y, 0)))))
    y = validize_mem (y);

  gcc_assert (mode != BLKmode);

  last_insn = emit_move_insn_1 (x, y);

  if (y_cst && REG_P (x)
      && (set = single_set (last_insn)) != NULL_RTX
      && SET_DEST (set) == x
      && ! rtx_equal_p (y_cst, SET_SRC (set)))
    set_unique_reg_note (last_insn, REG_EQUAL, y_cst);

  return last_insn;
}