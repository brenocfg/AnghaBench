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
struct TYPE_2__ {int gr_used_mask; } ;

/* Variables and functions */
 scalar_t__* call_used_regs ; 
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * global_regs ; 
 int last_scratch_gr_reg ; 

__attribute__((used)) static int
next_scratch_gr_reg (void)
{
  int i, regno;

  for (i = 0; i < 32; ++i)
    {
      regno = (last_scratch_gr_reg + i + 1) & 31;
      if (call_used_regs[regno]
	  && ! fixed_regs[regno]
	  && ! global_regs[regno]
	  && ((current_frame_info.gr_used_mask >> regno) & 1) == 0)
	{
	  last_scratch_gr_reg = regno;
	  return regno;
	}
    }

  /* There must be _something_ available.  */
  gcc_unreachable ();
}