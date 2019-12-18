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
typedef  enum attr_cirrus { ____Placeholder_attr_cirrus } attr_cirrus ;

/* Variables and functions */
 int CIRRUS_COMPARE ; 
 scalar_t__ CIRRUS_DOUBLE ; 
 scalar_t__ CIRRUS_MOVE ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ FLOAT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN ; 
 scalar_t__ JUMP_INSN ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ RETURN ; 
 scalar_t__ SET ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arm_cirrus_insn_p (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_memory_load_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_nop () ; 
 scalar_t__ get_attr_cirrus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_nonnote_insn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cirrus_reorg (rtx first)
{
  enum attr_cirrus attr;
  rtx body = PATTERN (first);
  rtx t;
  int nops;

  /* Any branch must be followed by 2 non Cirrus instructions.  */
  if (GET_CODE (first) == JUMP_INSN && GET_CODE (body) != RETURN)
    {
      nops = 0;
      t = next_nonnote_insn (first);

      if (arm_cirrus_insn_p (t))
	++ nops;

      if (arm_cirrus_insn_p (next_nonnote_insn (t)))
	++ nops;

      while (nops --)
	emit_insn_after (gen_nop (), first);

      return;
    }

  /* (float (blah)) is in parallel with a clobber.  */
  if (GET_CODE (body) == PARALLEL && XVECLEN (body, 0) > 0)
    body = XVECEXP (body, 0, 0);

  if (GET_CODE (body) == SET)
    {
      rtx lhs = XEXP (body, 0), rhs = XEXP (body, 1);

      /* cfldrd, cfldr64, cfstrd, cfstr64 must
	 be followed by a non Cirrus insn.  */
      if (get_attr_cirrus (first) == CIRRUS_DOUBLE)
	{
	  if (arm_cirrus_insn_p (next_nonnote_insn (first)))
	    emit_insn_after (gen_nop (), first);

	  return;
	}
      else if (arm_memory_load_p (first))
	{
	  unsigned int arm_regno;

	  /* Any ldr/cfmvdlr, ldr/cfmvdhr, ldr/cfmvsr, ldr/cfmv64lr,
	     ldr/cfmv64hr combination where the Rd field is the same
	     in both instructions must be split with a non Cirrus
	     insn.  Example:

	     ldr r0, blah
	     nop
	     cfmvsr mvf0, r0.  */

	  /* Get Arm register number for ldr insn.  */
	  if (GET_CODE (lhs) == REG)
	    arm_regno = REGNO (lhs);
	  else
	    {
	      gcc_assert (GET_CODE (rhs) == REG);
	      arm_regno = REGNO (rhs);
	    }

	  /* Next insn.  */
	  first = next_nonnote_insn (first);

	  if (! arm_cirrus_insn_p (first))
	    return;

	  body = PATTERN (first);

          /* (float (blah)) is in parallel with a clobber.  */
          if (GET_CODE (body) == PARALLEL && XVECLEN (body, 0))
	    body = XVECEXP (body, 0, 0);

	  if (GET_CODE (body) == FLOAT)
	    body = XEXP (body, 0);

	  if (get_attr_cirrus (first) == CIRRUS_MOVE
	      && GET_CODE (XEXP (body, 1)) == REG
	      && arm_regno == REGNO (XEXP (body, 1)))
	    emit_insn_after (gen_nop (), first);

	  return;
	}
    }

  /* get_attr cannot accept USE or CLOBBER.  */
  if (!first
      || GET_CODE (first) != INSN
      || GET_CODE (PATTERN (first)) == USE
      || GET_CODE (PATTERN (first)) == CLOBBER)
    return;

  attr = get_attr_cirrus (first);

  /* Any coprocessor compare instruction (cfcmps, cfcmpd, ...)
     must be followed by a non-coprocessor instruction.  */
  if (attr == CIRRUS_COMPARE)
    {
      nops = 0;

      t = next_nonnote_insn (first);

      if (arm_cirrus_insn_p (t))
	++ nops;

      if (arm_cirrus_insn_p (next_nonnote_insn (t)))
	++ nops;

      while (nops --)
	emit_insn_after (gen_nop (), first);

      return;
    }
}