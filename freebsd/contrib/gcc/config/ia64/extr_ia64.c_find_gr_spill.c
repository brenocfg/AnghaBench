#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int gr_used_mask; int n_local_regs; } ;

/* Variables and functions */
 int GR_REG (int) ; 
 int LOC_REG (int /*<<< orphan*/ ) ; 
 scalar_t__* call_used_regs ; 
 TYPE_1__ current_frame_info ; 
 scalar_t__ current_function_is_leaf ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int frame_pointer_needed ; 
 int /*<<< orphan*/ * global_regs ; 
 int /*<<< orphan*/ * regs_ever_live ; 

__attribute__((used)) static int
find_gr_spill (int try_locals)
{
  int regno;

  /* If this is a leaf function, first try an otherwise unused
     call-clobbered register.  */
  if (current_function_is_leaf)
    {
      for (regno = GR_REG (1); regno <= GR_REG (31); regno++)
	if (! regs_ever_live[regno]
	    && call_used_regs[regno]
	    && ! fixed_regs[regno]
	    && ! global_regs[regno]
	    && ((current_frame_info.gr_used_mask >> regno) & 1) == 0)
	  {
	    current_frame_info.gr_used_mask |= 1 << regno;
	    return regno;
	  }
    }

  if (try_locals)
    {
      regno = current_frame_info.n_local_regs;
      /* If there is a frame pointer, then we can't use loc79, because
	 that is HARD_FRAME_POINTER_REGNUM.  In particular, see the
	 reg_name switching code in ia64_expand_prologue.  */
      if (regno < (80 - frame_pointer_needed))
	{
	  current_frame_info.n_local_regs = regno + 1;
	  return LOC_REG (0) + regno;
	}
    }

  /* Failed to find a general register to spill to.  Must use stack.  */
  return 0;
}