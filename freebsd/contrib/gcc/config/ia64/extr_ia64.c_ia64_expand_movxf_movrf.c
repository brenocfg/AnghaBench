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
 scalar_t__ CONST_DOUBLE ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GR_REGNO_P (scalar_t__) ; 
 scalar_t__ MEM ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TImode ; 
 int WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assign_stack_temp (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SUBREG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_move_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 int /*<<< orphan*/  operand_subword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ register_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  spill_xfmode_rfmode_operand (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

bool
ia64_expand_movxf_movrf (enum machine_mode mode, rtx operands[])
{
  rtx op0 = operands[0];

  if (GET_CODE (op0) == SUBREG)
    op0 = SUBREG_REG (op0);

  /* We must support XFmode loads into general registers for stdarg/vararg,
     unprototyped calls, and a rare case where a long double is passed as
     an argument after a float HFA fills the FP registers.  We split them into
     DImode loads for convenience.  We also need to support XFmode stores
     for the last case.  This case does not happen for stdarg/vararg routines,
     because we do a block store to memory of unnamed arguments.  */

  if (GET_CODE (op0) == REG && GR_REGNO_P (REGNO (op0)))
    {
      rtx out[2];

      /* We're hoping to transform everything that deals with XFmode
	 quantities and GR registers early in the compiler.  */
      gcc_assert (!no_new_pseudos);

      /* Struct to register can just use TImode instead.  */
      if ((GET_CODE (operands[1]) == SUBREG
	   && GET_MODE (SUBREG_REG (operands[1])) == TImode)
	  || (GET_CODE (operands[1]) == REG
	      && GR_REGNO_P (REGNO (operands[1]))))
	{
	  rtx op1 = operands[1];

	  if (GET_CODE (op1) == SUBREG)
	    op1 = SUBREG_REG (op1);
	  else
	    op1 = gen_rtx_REG (TImode, REGNO (op1));

	  emit_move_insn (gen_rtx_REG (TImode, REGNO (op0)), op1);
	  return true;
	}

      if (GET_CODE (operands[1]) == CONST_DOUBLE)
	{
	  /* Don't word-swap when reading in the constant.  */
	  emit_move_insn (gen_rtx_REG (DImode, REGNO (op0)),
			  operand_subword (operands[1], WORDS_BIG_ENDIAN,
					   0, mode));
	  emit_move_insn (gen_rtx_REG (DImode, REGNO (op0) + 1),
			  operand_subword (operands[1], !WORDS_BIG_ENDIAN,
					   0, mode));
	  return true;
	}

      /* If the quantity is in a register not known to be GR, spill it.  */
      if (register_operand (operands[1], mode))
	operands[1] = spill_xfmode_rfmode_operand (operands[1], 1, mode);

      gcc_assert (GET_CODE (operands[1]) == MEM);

      /* Don't word-swap when reading in the value.  */
      out[0] = gen_rtx_REG (DImode, REGNO (op0));
      out[1] = gen_rtx_REG (DImode, REGNO (op0) + 1);

      emit_move_insn (out[0], adjust_address (operands[1], DImode, 0));
      emit_move_insn (out[1], adjust_address (operands[1], DImode, 8));
      return true;
    }

  if (GET_CODE (operands[1]) == REG && GR_REGNO_P (REGNO (operands[1])))
    {
      /* We're hoping to transform everything that deals with XFmode
	 quantities and GR registers early in the compiler.  */
      gcc_assert (!no_new_pseudos);

      /* Op0 can't be a GR_REG here, as that case is handled above.
	 If op0 is a register, then we spill op1, so that we now have a
	 MEM operand.  This requires creating an XFmode subreg of a TImode reg
	 to force the spill.  */
      if (register_operand (operands[0], mode))
	{
	  rtx op1 = gen_rtx_REG (TImode, REGNO (operands[1]));
	  op1 = gen_rtx_SUBREG (mode, op1, 0);
	  operands[1] = spill_xfmode_rfmode_operand (op1, 0, mode);
	}

      else
	{
	  rtx in[2];

	  gcc_assert (GET_CODE (operands[0]) == MEM);

	  /* Don't word-swap when writing out the value.  */
	  in[0] = gen_rtx_REG (DImode, REGNO (operands[1]));
	  in[1] = gen_rtx_REG (DImode, REGNO (operands[1]) + 1);

	  emit_move_insn (adjust_address (operands[0], DImode, 0), in[0]);
	  emit_move_insn (adjust_address (operands[0], DImode, 8), in[1]);
	  return true;
	}
    }

  if (!reload_in_progress && !reload_completed)
    {
      operands[1] = spill_xfmode_rfmode_operand (operands[1], 0, mode);

      if (GET_MODE (op0) == TImode && GET_CODE (op0) == REG)
	{
	  rtx memt, memx, in = operands[1];
	  if (CONSTANT_P (in))
	    in = validize_mem (force_const_mem (mode, in));
	  if (GET_CODE (in) == MEM)
	    memt = adjust_address (in, TImode, 0);
	  else
	    {
	      memt = assign_stack_temp (TImode, 16, 0);
	      memx = adjust_address (memt, mode, 0);
	      emit_move_insn (memx, in);
	    }
	  emit_move_insn (op0, memt);
	  return true;
	}

      if (!ia64_move_ok (operands[0], operands[1]))
	operands[1] = force_reg (mode, operands[1]);
    }

  return false;
}