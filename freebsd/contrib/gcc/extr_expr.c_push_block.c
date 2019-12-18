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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  GET_CLASS_NARROWEST_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  anti_adjust_stack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  negate_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int /*<<< orphan*/  virtual_outgoing_args_rtx ; 

rtx
push_block (rtx size, int extra, int below)
{
  rtx temp;

  size = convert_modes (Pmode, ptr_mode, size, 1);
  if (CONSTANT_P (size))
    anti_adjust_stack (plus_constant (size, extra));
  else if (REG_P (size) && extra == 0)
    anti_adjust_stack (size);
  else
    {
      temp = copy_to_mode_reg (Pmode, size);
      if (extra != 0)
	temp = expand_binop (Pmode, add_optab, temp, GEN_INT (extra),
			     temp, 0, OPTAB_LIB_WIDEN);
      anti_adjust_stack (temp);
    }

#ifndef STACK_GROWS_DOWNWARD
  if (0)
#else
  if (1)
#endif
    {
      temp = virtual_outgoing_args_rtx;
      if (extra != 0 && below)
	temp = plus_constant (temp, extra);
    }
  else
    {
      if (GET_CODE (size) == CONST_INT)
	temp = plus_constant (virtual_outgoing_args_rtx,
			      -INTVAL (size) - (below ? 0 : extra));
      else if (extra != 0 && !below)
	temp = gen_rtx_PLUS (Pmode, virtual_outgoing_args_rtx,
			     negate_rtx (Pmode, plus_constant (size, extra)));
      else
	temp = gen_rtx_PLUS (Pmode, virtual_outgoing_args_rtx,
			     negate_rtx (Pmode, size));
    }

  return memory_address (GET_CLASS_NARROWEST_MODE (MODE_INT), temp);
}