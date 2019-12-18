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
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_INSN_FUNCTION_BEG ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 int /*<<< orphan*/  REG_EQUIV ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  remove_note (scalar_t__,scalar_t__) ; 

void
fixup_tail_calls (void)
{
  rtx insn;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      /* There are never REG_EQUIV notes for the incoming arguments
	 after the NOTE_INSN_FUNCTION_BEG note, so stop if we see it.  */
      if (NOTE_P (insn)
	  && NOTE_LINE_NUMBER (insn) == NOTE_INSN_FUNCTION_BEG)
	break;

      while (1)
	{
	  rtx note = find_reg_note (insn, REG_EQUIV, 0);
	  if (note)
	    {
	      /* Remove the note and keep looking at the notes for
		 this insn.  */
	      remove_note (insn, note);
	      continue;
	    }
	  break;
	}
    }
}