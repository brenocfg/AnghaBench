#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {scalar_t__ next_bb; } ;

/* Variables and functions */
 int ADDR_DIFF_VEC ; 
 int ADDR_VEC ; 
#define  BARRIER 133 
 scalar_t__ BB_END (TYPE_1__*) ; 
 scalar_t__ BB_HEAD (scalar_t__) ; 
#define  CODE_LABEL 132 
 scalar_t__ EXIT_BLOCK_PTR ; 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  JUMP_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 131 
#define  NOTE_INSN_BLOCK_END 130 
#define  NOTE_INSN_DELETED 129 
#define  NOTE_INSN_DELETED_LABEL 128 
 int NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  reorder_insns (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
skip_insns_after_block (basic_block bb)
{
  rtx insn, last_insn, next_head, prev;

  next_head = NULL_RTX;
  if (bb->next_bb != EXIT_BLOCK_PTR)
    next_head = BB_HEAD (bb->next_bb);

  for (last_insn = insn = BB_END (bb); (insn = NEXT_INSN (insn)) != 0; )
    {
      if (insn == next_head)
	break;

      switch (GET_CODE (insn))
	{
	case BARRIER:
	  last_insn = insn;
	  continue;

	case NOTE:
	  switch (NOTE_LINE_NUMBER (insn))
	    {
	    case NOTE_INSN_BLOCK_END:
	      last_insn = insn;
	      continue;
	    case NOTE_INSN_DELETED:
	    case NOTE_INSN_DELETED_LABEL:
	      continue;

	    default:
	      continue;
	      break;
	    }
	  break;

	case CODE_LABEL:
	  if (NEXT_INSN (insn)
	      && JUMP_P (NEXT_INSN (insn))
	      && (GET_CODE (PATTERN (NEXT_INSN (insn))) == ADDR_VEC
		  || GET_CODE (PATTERN (NEXT_INSN (insn))) == ADDR_DIFF_VEC))
	    {
	      insn = NEXT_INSN (insn);
	      last_insn = insn;
	      continue;
	    }
	  break;

	default:
	  break;
	}

      break;
    }

  /* It is possible to hit contradictory sequence.  For instance:

     jump_insn
     NOTE_INSN_BLOCK_BEG
     barrier

     Where barrier belongs to jump_insn, but the note does not.  This can be
     created by removing the basic block originally following
     NOTE_INSN_BLOCK_BEG.  In such case reorder the notes.  */

  for (insn = last_insn; insn != BB_END (bb); insn = prev)
    {
      prev = PREV_INSN (insn);
      if (NOTE_P (insn))
	switch (NOTE_LINE_NUMBER (insn))
	  {
	  case NOTE_INSN_BLOCK_END:
	  case NOTE_INSN_DELETED:
	  case NOTE_INSN_DELETED_LABEL:
	    continue;
	  default:
	    reorder_insns (insn, insn, last_insn);
	  }
    }

  return last_insn;
}