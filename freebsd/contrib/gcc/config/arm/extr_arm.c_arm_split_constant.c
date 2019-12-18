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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ COND_EXEC ; 
 scalar_t__ COND_EXEC_TEST (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int MINUS ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int SET ; 
 int /*<<< orphan*/  after_arm_reorg ; 
 int arm_constant_limit ; 
 int arm_gen_constant (int,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  emit_set_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,scalar_t__,scalar_t__) ; 

int
arm_split_constant (enum rtx_code code, enum machine_mode mode, rtx insn,
		    HOST_WIDE_INT val, rtx target, rtx source, int subtargets)
{
  rtx cond;

  if (insn && GET_CODE (PATTERN (insn)) == COND_EXEC)
    cond = COND_EXEC_TEST (PATTERN (insn));
  else
    cond = NULL_RTX;

  if (subtargets || code == SET
      || (GET_CODE (target) == REG && GET_CODE (source) == REG
	  && REGNO (target) != REGNO (source)))
    {
      /* After arm_reorg has been called, we can't fix up expensive
	 constants by pushing them into memory so we must synthesize
	 them in-line, regardless of the cost.  This is only likely to
	 be more costly on chips that have load delay slots and we are
	 compiling without running the scheduler (so no splitting
	 occurred before the final instruction emission).

	 Ref: gcc -O1 -mcpu=strongarm gcc.c-torture/compile/980506-2.c
      */
      if (!after_arm_reorg
	  && !cond
	  && (arm_gen_constant (code, mode, NULL_RTX, val, target, source,
				1, 0)
	      > arm_constant_limit + (code != SET)))
	{
	  if (code == SET)
	    {
	      /* Currently SET is the only monadic value for CODE, all
		 the rest are diadic.  */
	      emit_set_insn (target, GEN_INT (val));
	      return 1;
	    }
	  else
	    {
	      rtx temp = subtargets ? gen_reg_rtx (mode) : target;

	      emit_set_insn (temp, GEN_INT (val));
	      /* For MINUS, the value is subtracted from, since we never
		 have subtraction of a constant.  */
	      if (code == MINUS)
		emit_set_insn (target, gen_rtx_MINUS (mode, temp, source));
	      else
		emit_set_insn (target,
			       gen_rtx_fmt_ee (code, mode, source, temp));
	      return 2;
	    }
	}
    }

  return arm_gen_constant (code, mode, cond, val, target, source, subtargets,
			   1);
}