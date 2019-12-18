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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {unsigned int global_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int GLOBAL_POINTER_REGNUM ; 
 int GP_REG_FIRST ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ MODE_FLOAT ; 
 scalar_t__ TARGET_ABICALLS ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ TARGET_NEWABI ; 
 scalar_t__ UNITS_PER_FPVALUE ; 
 int /*<<< orphan*/  aggregate_value_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * call_used_regs ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__ mips16_hard_float ; 
 scalar_t__* regs_ever_live ; 

__attribute__((used)) static bool
mips_save_reg_p (unsigned int regno)
{
  /* We only need to save $gp for NewABI PIC.  */
  if (regno == GLOBAL_POINTER_REGNUM)
    return (TARGET_ABICALLS && TARGET_NEWABI
	    && cfun->machine->global_pointer == regno);

  /* Check call-saved registers.  */
  if (regs_ever_live[regno] && !call_used_regs[regno])
    return true;

  /* We need to save the old frame pointer before setting up a new one.  */
  if (regno == HARD_FRAME_POINTER_REGNUM && frame_pointer_needed)
    return true;

  /* We need to save the incoming return address if it is ever clobbered
     within the function.  */
  if (regno == GP_REG_FIRST + 31 && regs_ever_live[regno])
    return true;

  if (TARGET_MIPS16)
    {
      tree return_type;

      return_type = DECL_RESULT (current_function_decl);

      /* $18 is a special case in mips16 code.  It may be used to call
	 a function which returns a floating point value, but it is
	 marked in call_used_regs.  */
      if (regno == GP_REG_FIRST + 18 && regs_ever_live[regno])
	return true;

      /* $31 is also a special case.  It will be used to copy a return
	 value into the floating point registers if the return value is
	 floating point.  */
      if (regno == GP_REG_FIRST + 31
	  && mips16_hard_float
	  && !aggregate_value_p (return_type, current_function_decl)
	  && GET_MODE_CLASS (DECL_MODE (return_type)) == MODE_FLOAT
	  && GET_MODE_SIZE (DECL_MODE (return_type)) <= UNITS_PER_FPVALUE)
	return true;
    }

  return false;
}