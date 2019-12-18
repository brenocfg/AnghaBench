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
struct TYPE_2__ {int reg_fp; int n_input_regs; int n_local_regs; } ;

/* Variables and functions */
 int HARD_FRAME_POINTER_REGNUM ; 
 int IN_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_REGNO_P (int) ; 
 int LOC_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ LOC_REGNO_P (int) ; 
 int OUT_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ OUT_REGNO_P (int) ; 
 TYPE_1__ current_frame_info ; 

int
ia64_dbx_register_number (int regno)
{
  /* In ia64_expand_prologue we quite literally renamed the frame pointer
     from its home at loc79 to something inside the register frame.  We
     must perform the same renumbering here for the debug info.  */
  if (current_frame_info.reg_fp)
    {
      if (regno == HARD_FRAME_POINTER_REGNUM)
	regno = current_frame_info.reg_fp;
      else if (regno == current_frame_info.reg_fp)
	regno = HARD_FRAME_POINTER_REGNUM;
    }

  if (IN_REGNO_P (regno))
    return 32 + regno - IN_REG (0);
  else if (LOC_REGNO_P (regno))
    return 32 + current_frame_info.n_input_regs + regno - LOC_REG (0);
  else if (OUT_REGNO_P (regno))
    return (32 + current_frame_info.n_input_regs
	    + current_frame_info.n_local_regs + regno - OUT_REG (0));
  else
    return regno;
}