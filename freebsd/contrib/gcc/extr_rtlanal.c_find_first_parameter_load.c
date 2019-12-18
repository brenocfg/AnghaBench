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
struct parms_set_data {int nregs; int /*<<< orphan*/  regs; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CALL_INSN_FUNCTION_USAGE (scalar_t__) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  FUNCTION_ARG_REGNO_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ USE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct parms_set_data*) ; 
 int /*<<< orphan*/  parms_set ; 

rtx
find_first_parameter_load (rtx call_insn, rtx boundary)
{
  struct parms_set_data parm;
  rtx p, before, first_set;

  /* Since different machines initialize their parameter registers
     in different orders, assume nothing.  Collect the set of all
     parameter registers.  */
  CLEAR_HARD_REG_SET (parm.regs);
  parm.nregs = 0;
  for (p = CALL_INSN_FUNCTION_USAGE (call_insn); p; p = XEXP (p, 1))
    if (GET_CODE (XEXP (p, 0)) == USE
	&& REG_P (XEXP (XEXP (p, 0), 0)))
      {
	gcc_assert (REGNO (XEXP (XEXP (p, 0), 0)) < FIRST_PSEUDO_REGISTER);

	/* We only care about registers which can hold function
	   arguments.  */
	if (!FUNCTION_ARG_REGNO_P (REGNO (XEXP (XEXP (p, 0), 0))))
	  continue;

	SET_HARD_REG_BIT (parm.regs, REGNO (XEXP (XEXP (p, 0), 0)));
	parm.nregs++;
      }
  before = call_insn;
  first_set = call_insn;

  /* Search backward for the first set of a register in this set.  */
  while (parm.nregs && before != boundary)
    {
      before = PREV_INSN (before);

      /* It is possible that some loads got CSEed from one call to
         another.  Stop in that case.  */
      if (CALL_P (before))
	break;

      /* Our caller needs either ensure that we will find all sets
         (in case code has not been optimized yet), or take care
         for possible labels in a way by setting boundary to preceding
         CODE_LABEL.  */
      if (LABEL_P (before))
	{
	  gcc_assert (before == boundary);
	  break;
	}

      if (INSN_P (before))
	{
	  int nregs_old = parm.nregs;
	  note_stores (PATTERN (before), parms_set, &parm);
	  /* If we found something that did not set a parameter reg,
	     we're done.  Do not keep going, as that might result
	     in hoisting an insn before the setting of a pseudo
	     that is used by the hoisted insn. */
	  if (nregs_old != parm.nregs)
	    first_set = before;
	  else
	    break;
	}
    }
  return first_set;
}