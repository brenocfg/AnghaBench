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

/* Variables and functions */
 scalar_t__ ADDRESS ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  CONST_OR_PURE_CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ Pmode ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ ZERO_EXTRACT ; 
 scalar_t__ expr_equiv_p (scalar_t__,scalar_t__) ; 
 scalar_t__ find_base_term (scalar_t__) ; 
 int find_loads (scalar_t__,scalar_t__,int) ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 scalar_t__ output_dependence (scalar_t__,scalar_t__) ; 
 scalar_t__ pure_call_p (scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 

__attribute__((used)) static bool
store_killed_in_insn (rtx x, rtx x_regs, rtx insn, int after)
{
  rtx reg, base, note;

  if (!INSN_P (insn))
    return false;

  if (CALL_P (insn))
    {
      /* A normal or pure call might read from pattern,
	 but a const call will not.  */
      if (! CONST_OR_PURE_CALL_P (insn) || pure_call_p (insn))
	return true;

      /* But even a const call reads its parameters.  Check whether the
	 base of some of registers used in mem is stack pointer.  */
      for (reg = x_regs; reg; reg = XEXP (reg, 1))
	{
	  base = find_base_term (XEXP (reg, 0));
	  if (!base
	      || (GET_CODE (base) == ADDRESS
		  && GET_MODE (base) == Pmode
		  && XEXP (base, 0) == stack_pointer_rtx))
	    return true;
	}

      return false;
    }

  if (GET_CODE (PATTERN (insn)) == SET)
    {
      rtx pat = PATTERN (insn);
      rtx dest = SET_DEST (pat);

      if (GET_CODE (dest) == ZERO_EXTRACT)
	dest = XEXP (dest, 0);

      /* Check for memory stores to aliased objects.  */
      if (MEM_P (dest)
	  && !expr_equiv_p (dest, x))
	{
	  if (after)
	    {
	      if (output_dependence (dest, x))
		return true;
	    }
	  else
	    {
	      if (output_dependence (x, dest))
		return true;
	    }
	}
      if (find_loads (SET_SRC (pat), x, after))
	return true;
    }
  else if (find_loads (PATTERN (insn), x, after))
    return true;

  /* If this insn has a REG_EQUAL or REG_EQUIV note referencing a memory
     location aliased with X, then this insn kills X.  */
  note = find_reg_equal_equiv_note (insn);
  if (! note)
    return false;
  note = XEXP (note, 0);

  /* However, if the note represents a must alias rather than a may
     alias relationship, then it does not kill X.  */
  if (expr_equiv_p (note, x))
    return false;

  /* See if there are any aliased loads in the note.  */
  return find_loads (note, x, after);
}