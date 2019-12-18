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
 scalar_t__ BARRIER_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ prev_nonnote_insn (scalar_t__) ; 
 int /*<<< orphan*/  reorder_insns (scalar_t__,scalar_t__,scalar_t__) ; 

unsigned int
cleanup_barriers (void)
{
  rtx insn, next, prev;
  for (insn = get_insns (); insn; insn = next)
    {
      next = NEXT_INSN (insn);
      if (BARRIER_P (insn))
	{
	  prev = prev_nonnote_insn (insn);
	  if (BARRIER_P (prev))
	    delete_insn (insn);
	  else if (prev != PREV_INSN (insn))
	    reorder_insns (insn, insn, prev);
	}
    }
  return 0;
}