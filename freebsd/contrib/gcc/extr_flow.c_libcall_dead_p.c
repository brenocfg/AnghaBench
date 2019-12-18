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
struct propagate_block_info {int dummy; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CALL ; 
 int /*<<< orphan*/  CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_dead_p (struct propagate_block_info*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static int
libcall_dead_p (struct propagate_block_info *pbi, rtx note, rtx insn)
{
  rtx x = single_set (insn);

  if (x)
    {
      rtx r = SET_SRC (x);

      if (REG_P (r) || GET_CODE (r) == SUBREG)
	{
	  rtx call = XEXP (note, 0);
	  rtx call_pat;
	  int i;

	  /* Find the call insn.  */
	  while (call != insn && !CALL_P (call))
	    call = NEXT_INSN (call);

	  /* If there is none, do nothing special,
	     since ordinary death handling can understand these insns.  */
	  if (call == insn)
	    return 0;

	  /* See if the hard reg holding the value is dead.
	     If this is a PARALLEL, find the call within it.  */
	  call_pat = PATTERN (call);
	  if (GET_CODE (call_pat) == PARALLEL)
	    {
	      for (i = XVECLEN (call_pat, 0) - 1; i >= 0; i--)
		if (GET_CODE (XVECEXP (call_pat, 0, i)) == SET
		    && GET_CODE (SET_SRC (XVECEXP (call_pat, 0, i))) == CALL)
		  break;

	      /* This may be a library call that is returning a value
		 via invisible pointer.  Do nothing special, since
		 ordinary death handling can understand these insns.  */
	      if (i < 0)
		return 0;

	      call_pat = XVECEXP (call_pat, 0, i);
	    }

	  if (! insn_dead_p (pbi, call_pat, 1, REG_NOTES (call)))
	    return 0;

	  while ((insn = PREV_INSN (insn)) != call)
	    {
	      if (! INSN_P (insn))
		continue;
	      if (! insn_dead_p (pbi, PATTERN (insn), 0, REG_NOTES (insn)))
		return 0;
	    }
	  return 1;
	}
    }
  return 0;
}