#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ force_align_arg_pointer; } ;

/* Variables and functions */
 unsigned int EH_RETURN_DATA_REGNO (unsigned int) ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
 unsigned int INVALID_REGNUM ; 
 unsigned int REAL_PIC_OFFSET_TABLE_REGNUM ; 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/ * call_used_regs ; 
 TYPE_2__* cfun ; 
 scalar_t__ current_function_calls_eh_return ; 
 scalar_t__ current_function_profile ; 
 scalar_t__ current_function_uses_const_pool ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 unsigned int ix86_select_alt_pic_regnum () ; 
 scalar_t__ pic_offset_table_rtx ; 
 scalar_t__* regs_ever_live ; 

__attribute__((used)) static int
ix86_save_reg (unsigned int regno, int maybe_eh_return)
{
  if (pic_offset_table_rtx
      && regno == REAL_PIC_OFFSET_TABLE_REGNUM
      && (regs_ever_live[REAL_PIC_OFFSET_TABLE_REGNUM]
	  || current_function_profile
	  || current_function_calls_eh_return
	  || current_function_uses_const_pool))
    {
      if (ix86_select_alt_pic_regnum () != INVALID_REGNUM)
	return 0;
      return 1;
    }

  if (current_function_calls_eh_return && maybe_eh_return)
    {
      unsigned i;
      for (i = 0; ; i++)
	{
	  unsigned test = EH_RETURN_DATA_REGNO (i);
	  if (test == INVALID_REGNUM)
	    break;
	  if (test == regno)
	    return 1;
	}
    }

  if (cfun->machine->force_align_arg_pointer
      && regno == REGNO (cfun->machine->force_align_arg_pointer))
    return 1;

  return (regs_ever_live[regno]
	  && !call_used_regs[regno]
	  && !fixed_regs[regno]
	  && (regno != HARD_FRAME_POINTER_REGNUM || !frame_pointer_needed));
}