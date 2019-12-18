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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DImode ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ GP_REG_P (int) ; 
 int HI_REGNUM ; 
 int LO_REGNUM ; 
 scalar_t__ MD_REG_P (int) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mfhilo_di (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mfhilo_si (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_last_insn () ; 
 int /*<<< orphan*/  mips_legitimize_const_move (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_or_0_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mips_legitimize_move (enum machine_mode mode, rtx dest, rtx src)
{
  if (!register_operand (dest, mode) && !reg_or_0_operand (src, mode))
    {
      emit_move_insn (dest, force_reg (mode, src));
      return true;
    }

  /* Check for individual, fully-reloaded mflo and mfhi instructions.  */
  if (GET_MODE_SIZE (mode) <= UNITS_PER_WORD
      && REG_P (src) && MD_REG_P (REGNO (src))
      && REG_P (dest) && GP_REG_P (REGNO (dest)))
    {
      int other_regno = REGNO (src) == HI_REGNUM ? LO_REGNUM : HI_REGNUM;
      if (GET_MODE_SIZE (mode) <= 4)
	emit_insn (gen_mfhilo_si (gen_rtx_REG (SImode, REGNO (dest)),
				  gen_rtx_REG (SImode, REGNO (src)),
				  gen_rtx_REG (SImode, other_regno)));
      else
	emit_insn (gen_mfhilo_di (gen_rtx_REG (DImode, REGNO (dest)),
				  gen_rtx_REG (DImode, REGNO (src)),
				  gen_rtx_REG (DImode, other_regno)));
      return true;
    }

  /* We need to deal with constants that would be legitimate
     immediate_operands but not legitimate move_operands.  */
  if (CONSTANT_P (src) && !move_operand (src, mode))
    {
      mips_legitimize_const_move (mode, dest, src);
      set_unique_reg_note (get_last_insn (), REG_EQUAL, copy_rtx (src));
      return true;
    }
  return false;
}