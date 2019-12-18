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

/* Variables and functions */
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 int BARRIER ; 
 scalar_t__ BARRIER_P (scalar_t__) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int CODE_LABEL ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN_DELETED_P (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_NUSES (scalar_t__) ; 
 int LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 int NOTE ; 
 scalar_t__ NOTE_INSN_FUNCTION_END ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ REG_LABEL ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 scalar_t__ tablejump_p (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

rtx
delete_related_insns (rtx insn)
{
  int was_code_label = (LABEL_P (insn));
  rtx note;
  rtx next = NEXT_INSN (insn), prev = PREV_INSN (insn);

  while (next && INSN_DELETED_P (next))
    next = NEXT_INSN (next);

  /* This insn is already deleted => return first following nondeleted.  */
  if (INSN_DELETED_P (insn))
    return next;

  delete_insn (insn);

  /* If instruction is followed by a barrier,
     delete the barrier too.  */

  if (next != 0 && BARRIER_P (next))
    delete_insn (next);

  /* If deleting a jump, decrement the count of the label,
     and delete the label if it is now unused.  */

  if (JUMP_P (insn) && JUMP_LABEL (insn))
    {
      rtx lab = JUMP_LABEL (insn), lab_next;

      if (LABEL_NUSES (lab) == 0)
	{
	  /* This can delete NEXT or PREV,
	     either directly if NEXT is JUMP_LABEL (INSN),
	     or indirectly through more levels of jumps.  */
	  delete_related_insns (lab);

	  /* I feel a little doubtful about this loop,
	     but I see no clean and sure alternative way
	     to find the first insn after INSN that is not now deleted.
	     I hope this works.  */
	  while (next && INSN_DELETED_P (next))
	    next = NEXT_INSN (next);
	  return next;
	}
      else if (tablejump_p (insn, NULL, &lab_next))
	{
	  /* If we're deleting the tablejump, delete the dispatch table.
	     We may not be able to kill the label immediately preceding
	     just yet, as it might be referenced in code leading up to
	     the tablejump.  */
	  delete_related_insns (lab_next);
	}
    }

  /* Likewise if we're deleting a dispatch table.  */

  if (JUMP_P (insn)
      && (GET_CODE (PATTERN (insn)) == ADDR_VEC
	  || GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC))
    {
      rtx pat = PATTERN (insn);
      int i, diff_vec_p = GET_CODE (pat) == ADDR_DIFF_VEC;
      int len = XVECLEN (pat, diff_vec_p);

      for (i = 0; i < len; i++)
	if (LABEL_NUSES (XEXP (XVECEXP (pat, diff_vec_p, i), 0)) == 0)
	  delete_related_insns (XEXP (XVECEXP (pat, diff_vec_p, i), 0));
      while (next && INSN_DELETED_P (next))
	next = NEXT_INSN (next);
      return next;
    }

  /* Likewise for an ordinary INSN / CALL_INSN with a REG_LABEL note.  */
  if (NONJUMP_INSN_P (insn) || CALL_P (insn))
    for (note = REG_NOTES (insn); note; note = XEXP (note, 1))
      if (REG_NOTE_KIND (note) == REG_LABEL
	  /* This could also be a NOTE_INSN_DELETED_LABEL note.  */
	  && LABEL_P (XEXP (note, 0)))
	if (LABEL_NUSES (XEXP (note, 0)) == 0)
	  delete_related_insns (XEXP (note, 0));

  while (prev && (INSN_DELETED_P (prev) || NOTE_P (prev)))
    prev = PREV_INSN (prev);

  /* If INSN was a label and a dispatch table follows it,
     delete the dispatch table.  The tablejump must have gone already.
     It isn't useful to fall through into a table.  */

  if (was_code_label
      && NEXT_INSN (insn) != 0
      && JUMP_P (NEXT_INSN (insn))
      && (GET_CODE (PATTERN (NEXT_INSN (insn))) == ADDR_VEC
	  || GET_CODE (PATTERN (NEXT_INSN (insn))) == ADDR_DIFF_VEC))
    next = delete_related_insns (NEXT_INSN (insn));

  /* If INSN was a label, delete insns following it if now unreachable.  */

  if (was_code_label && prev && BARRIER_P (prev))
    {
      enum rtx_code code;
      while (next)
	{
	  code = GET_CODE (next);
	  if (code == NOTE
	      && NOTE_LINE_NUMBER (next) != NOTE_INSN_FUNCTION_END)
	    next = NEXT_INSN (next);
	  /* Keep going past other deleted labels to delete what follows.  */
	  else if (code == CODE_LABEL && INSN_DELETED_P (next))
	    next = NEXT_INSN (next);
	  else if (code == BARRIER || INSN_P (next))
	    /* Note: if this deletes a jump, it can cause more
	       deletion of unreachable code, after a different label.
	       As long as the value from this recursive call is correct,
	       this invocation functions correctly.  */
	    next = delete_related_insns (next);
	  else
	    break;
	}
    }

  return next;
}