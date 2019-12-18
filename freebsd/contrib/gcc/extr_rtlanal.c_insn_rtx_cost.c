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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int COSTS_N_INSNS (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtx_cost (int /*<<< orphan*/ ,scalar_t__) ; 

int
insn_rtx_cost (rtx pat)
{
  int i, cost;
  rtx set;

  /* Extract the single set rtx from the instruction pattern.
     We can't use single_set since we only have the pattern.  */
  if (GET_CODE (pat) == SET)
    set = pat;
  else if (GET_CODE (pat) == PARALLEL)
    {
      set = NULL_RTX;
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx x = XVECEXP (pat, 0, i);
	  if (GET_CODE (x) == SET)
	    {
	      if (set)
		return 0;
	      set = x;
	    }
	}
      if (!set)
	return 0;
    }
  else
    return 0;

  cost = rtx_cost (SET_SRC (set), SET);
  return cost > 0 ? cost : COSTS_N_INSNS (1);
}