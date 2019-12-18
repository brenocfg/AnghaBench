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
 int DFmode ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ current_function_calls_eh_return ; 
 scalar_t__ current_function_calls_setjmp ; 
 scalar_t__ current_function_has_nonlocal_goto ; 
 scalar_t__ get_insns () ; 

__attribute__((used)) static bool
spe_func_has_64bit_regs_p (void)
{
  rtx insns, insn;

  /* Functions that save and restore all the call-saved registers will
     need to save/restore the registers in 64-bits.  */
  if (current_function_calls_eh_return
      || current_function_calls_setjmp
      || current_function_has_nonlocal_goto)
    return true;

  insns = get_insns ();

  for (insn = NEXT_INSN (insns); insn != NULL_RTX; insn = NEXT_INSN (insn))
    {
      if (INSN_P (insn))
	{
	  rtx i;

	  /* FIXME: This should be implemented with attributes...

	         (set_attr "spe64" "true")....then,
	         if (get_spe64(insn)) return true;

	     It's the only reliable way to do the stuff below.  */

	  i = PATTERN (insn);
	  if (GET_CODE (i) == SET)
	    {
	      enum machine_mode mode = GET_MODE (SET_SRC (i));

	      if (SPE_VECTOR_MODE (mode))
		return true;
	      if (TARGET_E500_DOUBLE && mode == DFmode)
		return true;
	    }
	}
    }

  return false;
}