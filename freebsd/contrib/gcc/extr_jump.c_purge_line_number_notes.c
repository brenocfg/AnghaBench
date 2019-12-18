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
 scalar_t__ NOTE_SOURCE_FILE (scalar_t__) ; 
 scalar_t__ NOTE_SOURCE_LOCATION (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  delete_related_insns (scalar_t__) ; 
 scalar_t__ get_insns () ; 

unsigned int
purge_line_number_notes (void)
{
  rtx last_note = 0;
  rtx insn;
  /* Delete extraneous line number notes.
     Note that two consecutive notes for different lines are not really
     extraneous.  There should be some indication where that line belonged,
     even if it became empty.  */

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    if (NOTE_P (insn))
      {
	if (NOTE_LINE_NUMBER (insn) == NOTE_INSN_FUNCTION_BEG)
	  /* Any previous line note was for the prologue; gdb wants a new
	     note after the prologue even if it is for the same line.  */
	  last_note = NULL_RTX;
	else if (NOTE_LINE_NUMBER (insn) >= 0)
	  {
	    /* Delete this note if it is identical to previous note.  */
	    if (last_note
#ifdef USE_MAPPED_LOCATION
		&& NOTE_SOURCE_LOCATION (insn) == NOTE_SOURCE_LOCATION (last_note)
#else
		&& NOTE_SOURCE_FILE (insn) == NOTE_SOURCE_FILE (last_note)
		&& NOTE_LINE_NUMBER (insn) == NOTE_LINE_NUMBER (last_note)
#endif
)
	      {
		delete_related_insns (insn);
		continue;
	      }

	    last_note = insn;
	  }
      }
  return 0;
}