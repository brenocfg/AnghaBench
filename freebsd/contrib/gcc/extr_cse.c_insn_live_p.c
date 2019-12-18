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
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_non_call_exceptions ; 
 scalar_t__ may_trap_p (int /*<<< orphan*/ ) ; 
 int set_live_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
insn_live_p (rtx insn, int *counts)
{
  int i;
  if (flag_non_call_exceptions && may_trap_p (PATTERN (insn)))
    return true;
  else if (GET_CODE (PATTERN (insn)) == SET)
    return set_live_p (PATTERN (insn), insn, counts);
  else if (GET_CODE (PATTERN (insn)) == PARALLEL)
    {
      for (i = XVECLEN (PATTERN (insn), 0) - 1; i >= 0; i--)
	{
	  rtx elt = XVECEXP (PATTERN (insn), 0, i);

	  if (GET_CODE (elt) == SET)
	    {
	      if (set_live_p (elt, insn, counts))
		return true;
	    }
	  else if (GET_CODE (elt) != CLOBBER && GET_CODE (elt) != USE)
	    return true;
	}
      return false;
    }
  else
    return true;
}