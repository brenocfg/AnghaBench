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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
#define  BARRIER 133 
 scalar_t__ BARRIER_P (scalar_t__) ; 
#define  CALL_INSN 132 
#define  CODE_LABEL 131 
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 int GET_CODE (scalar_t__) ; 
#define  INSN 130 
#define  JUMP_INSN 129 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 128 
 int NOTE_INSN_BASIC_BLOCK ; 
 int NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  clear_aux_for_blocks () ; 
 scalar_t__ control_flow_insn_p (scalar_t__) ; 
 int /*<<< orphan*/  create_basic_block_structure (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ delete_insn (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ inside_basic_block_p (scalar_t__) ; 
 scalar_t__ last_basic_block ; 
 scalar_t__ n_basic_blocks ; 

__attribute__((used)) static void
find_basic_blocks_1 (rtx f)
{
  rtx insn, next;
  rtx bb_note = NULL_RTX;
  rtx head = NULL_RTX;
  rtx end = NULL_RTX;
  basic_block prev = ENTRY_BLOCK_PTR;

  /* We process the instructions in a slightly different way than we did
     previously.  This is so that we see a NOTE_BASIC_BLOCK after we have
     closed out the previous block, so that it gets attached at the proper
     place.  Since this form should be equivalent to the previous,
     count_basic_blocks continues to use the old form as a check.  */

  for (insn = f; insn; insn = next)
    {
      enum rtx_code code = GET_CODE (insn);

      next = NEXT_INSN (insn);

      if ((LABEL_P (insn) || BARRIER_P (insn))
	  && head)
	{
	  prev = create_basic_block_structure (head, end, bb_note, prev);
	  head = end = NULL_RTX;
	  bb_note = NULL_RTX;
	}

      if (inside_basic_block_p (insn))
	{
	  if (head == NULL_RTX)
	    head = insn;
	  end = insn;
	}

      if (head && control_flow_insn_p (insn))
	{
	  prev = create_basic_block_structure (head, end, bb_note, prev);
	  head = end = NULL_RTX;
	  bb_note = NULL_RTX;
	}

      switch (code)
	{
	case NOTE:
	  {
	    int kind = NOTE_LINE_NUMBER (insn);

	    /* Look for basic block notes with which to keep the
	       basic_block_info pointers stable.  Unthread the note now;
	       we'll put it back at the right place in create_basic_block.
	       Or not at all if we've already found a note in this block.  */
	    if (kind == NOTE_INSN_BASIC_BLOCK)
	      {
		if (bb_note == NULL_RTX)
		  bb_note = insn;
		else
		  next = delete_insn (insn);
	      }
	    break;
	  }

	case CODE_LABEL:
	case JUMP_INSN:
	case CALL_INSN:
	case INSN:
	case BARRIER:
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  if (head != NULL_RTX)
    create_basic_block_structure (head, end, bb_note, prev);
  else if (bb_note)
    delete_insn (bb_note);

  gcc_assert (last_basic_block == n_basic_blocks);

  clear_aux_for_blocks ();
}