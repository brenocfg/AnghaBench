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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const_high_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_HIGH (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IOR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 int /*<<< orphan*/  small_int_operand (int /*<<< orphan*/ ,int) ; 

void
sparc_emit_set_const32 (rtx op0, rtx op1)
{
  enum machine_mode mode = GET_MODE (op0);
  rtx temp;

  if (reload_in_progress || reload_completed)
    temp = op0;
  else
    temp = gen_reg_rtx (mode);

  if (GET_CODE (op1) == CONST_INT)
    {
      gcc_assert (!small_int_operand (op1, mode)
		  && !const_high_operand (op1, mode));

      /* Emit them as real moves instead of a HIGH/LO_SUM,
	 this way CSE can see everything and reuse intermediate
	 values if it wants.  */
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      GEN_INT (INTVAL (op1)
			        & ~(HOST_WIDE_INT)0x3ff)));

      emit_insn (gen_rtx_SET (VOIDmode,
			      op0,
			      gen_rtx_IOR (mode, temp,
					   GEN_INT (INTVAL (op1) & 0x3ff))));
    }
  else
    {
      /* A symbol, emit in the traditional way.  */
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      gen_rtx_HIGH (mode, op1)));
      emit_insn (gen_rtx_SET (VOIDmode,
			      op0, gen_rtx_LO_SUM (mode, temp, op1)));
    }
}