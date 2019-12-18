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
 int ADDR_DIFF_VEC ; 
 int ADDR_VEC ; 
#define  BARRIER 142 
#define  CALL_INSN 141 
#define  CODE_LABEL 140 
 int GET_CODE (scalar_t__) ; 
#define  INSN 139 
#define  JUMP_INSN 138 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 137 
#define  NOTE_INSN_BASIC_BLOCK 136 
#define  NOTE_INSN_DELETED 135 
#define  NOTE_INSN_DELETED_LABEL 134 
#define  NOTE_INSN_EPILOGUE_BEG 133 
#define  NOTE_INSN_FUNCTION_BEG 132 
#define  NOTE_INSN_FUNCTION_END 131 
#define  NOTE_INSN_PROLOGUE_END 130 
#define  NOTE_INSN_REPEATED_LINE_NUMBER 129 
#define  NOTE_INSN_SWITCH_TEXT_SECTIONS 128 
 int /*<<< orphan*/  NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_copy_of_insn_after (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_note (int) ; 
 int /*<<< orphan*/  emit_note_copy (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_last_insn () ; 

rtx
duplicate_insn_chain (rtx from, rtx to)
{
  rtx insn, last;

  /* Avoid updating of boundaries of previous basic block.  The
     note will get removed from insn stream in fixup.  */
  last = emit_note (NOTE_INSN_DELETED);

  /* Create copy at the end of INSN chain.  The chain will
     be reordered later.  */
  for (insn = from; insn != NEXT_INSN (to); insn = NEXT_INSN (insn))
    {
      switch (GET_CODE (insn))
	{
	case INSN:
	case CALL_INSN:
	case JUMP_INSN:
	  /* Avoid copying of dispatch tables.  We never duplicate
	     tablejumps, so this can hit only in case the table got
	     moved far from original jump.  */
	  if (GET_CODE (PATTERN (insn)) == ADDR_VEC
	      || GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC)
	    break;
	  emit_copy_of_insn_after (insn, get_last_insn ());
	  break;

	case CODE_LABEL:
	  break;

	case BARRIER:
	  emit_barrier ();
	  break;

	case NOTE:
	  switch (NOTE_LINE_NUMBER (insn))
	    {
	      /* In case prologue is empty and function contain label
		 in first BB, we may want to copy the block.  */
	    case NOTE_INSN_PROLOGUE_END:

	    case NOTE_INSN_DELETED:
	    case NOTE_INSN_DELETED_LABEL:
	      /* No problem to strip these.  */
	    case NOTE_INSN_EPILOGUE_BEG:
	    case NOTE_INSN_FUNCTION_END:
	      /* Debug code expect these notes to exist just once.
		 Keep them in the master copy.
		 ??? It probably makes more sense to duplicate them for each
		 epilogue copy.  */
	    case NOTE_INSN_FUNCTION_BEG:
	      /* There is always just single entry to function.  */
	    case NOTE_INSN_BASIC_BLOCK:
	      break;

	    case NOTE_INSN_REPEATED_LINE_NUMBER:
	    case NOTE_INSN_SWITCH_TEXT_SECTIONS:
	      emit_note_copy (insn);
	      break;

	    default:
	      /* All other notes should have already been eliminated.
	       */
	      gcc_assert (NOTE_LINE_NUMBER (insn) >= 0);

	      /* It is possible that no_line_number is set and the note
		 won't be emitted.  */
	      emit_note_copy (insn);
	    }
	  break;
	default:
	  gcc_unreachable ();
	}
    }
  insn = NEXT_INSN (last);
  delete_insn (last);
  return insn;
}