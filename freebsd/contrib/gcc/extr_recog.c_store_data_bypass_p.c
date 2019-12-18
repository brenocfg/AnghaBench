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
typedef  int rtx ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int PATTERN (int) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int) ; 
 int XVECEXP (int,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int single_set (int) ; 

int
store_data_bypass_p (rtx out_insn, rtx in_insn)
{
  rtx out_set, in_set;

  in_set = single_set (in_insn);
  gcc_assert (in_set);

  if (!MEM_P (SET_DEST (in_set)))
    return false;

  out_set = single_set (out_insn);
  if (out_set)
    {
      if (reg_mentioned_p (SET_DEST (out_set), SET_DEST (in_set)))
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

	  if (reg_mentioned_p (SET_DEST (exp), SET_DEST (in_set)))
	    return false;
	}
    }

  return true;
}