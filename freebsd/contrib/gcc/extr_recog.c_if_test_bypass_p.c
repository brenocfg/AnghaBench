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
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ IF_THEN_ELSE ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ single_set (scalar_t__) ; 

int
if_test_bypass_p (rtx out_insn, rtx in_insn)
{
  rtx out_set, in_set;

  in_set = single_set (in_insn);
  if (! in_set)
    {
      gcc_assert (JUMP_P (in_insn) || CALL_P (in_insn));
      return false;
    }

  if (GET_CODE (SET_SRC (in_set)) != IF_THEN_ELSE)
    return false;
  in_set = SET_SRC (in_set);

  out_set = single_set (out_insn);
  if (out_set)
    {
      if (reg_mentioned_p (SET_DEST (out_set), XEXP (in_set, 1))
	  || reg_mentioned_p (SET_DEST (out_set), XEXP (in_set, 2)))
	return false;
    }
  else
    {
      rtx out_pat;
      int i;

      out_pat = PATTERN (out_insn);
      gcc_assert (GET_CODE (out_pat) == PARALLEL);

      for (i = 0; i < XVECLEN (out_pat, 0); i++)
	{
	  rtx exp = XVECEXP (out_pat, 0, i);

	  if (GET_CODE (exp) == CLOBBER)
	    continue;

	  gcc_assert (GET_CODE (exp) == SET);

	  if (reg_mentioned_p (SET_DEST (out_set), XEXP (in_set, 1))
	      || reg_mentioned_p (SET_DEST (out_set), XEXP (in_set, 2)))
	    return false;
	}
    }

  return true;
}