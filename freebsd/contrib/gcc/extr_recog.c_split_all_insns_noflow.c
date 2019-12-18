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
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn_and_edges (scalar_t__) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ reload_completed ; 
 scalar_t__ set_noop_p (scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 int /*<<< orphan*/  split_insn (scalar_t__) ; 

unsigned int
split_all_insns_noflow (void)
{
  rtx next, insn;

  for (insn = get_insns (); insn; insn = next)
    {
      next = NEXT_INSN (insn);
      if (INSN_P (insn))
	{
	  /* Don't split no-op move insns.  These should silently
	     disappear later in final.  Splitting such insns would
	     break the code that handles REG_NO_CONFLICT blocks.  */
	  rtx set = single_set (insn);
	  if (set && set_noop_p (set))
	    {
	      /* Nops get in the way while scheduling, so delete them
		 now if register allocation has already been done.  It
		 is too risky to try to do this before register
		 allocation, and there are unlikely to be very many
		 nops then anyways.

		 ??? Should we use delete_insn when the CFG isn't valid?  */
	      if (reload_completed)
		delete_insn_and_edges (insn);
	    }
	  else
	    split_insn (insn);
	}
    }
  return 0;
}