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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  PointHandle ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PC_REGNUM ; 
 int RDIError_BreakpointReached ; 
 int RDIError_NoError ; 
 int angel_RDI_execute (int /*<<< orphan*/ *) ; 
 int angel_RDI_step (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_get_next_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_rdi_insert_breakpoint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  arm_rdi_remove_breakpoint (int /*<<< orphan*/ ,char*) ; 
 int execute_status ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_rdi_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  int rslt;
  PointHandle point;

  if (0 /* turn on when hardware supports single-stepping */ )
    {
      rslt = angel_RDI_step (1, &point);
      if (rslt != RDIError_NoError)
	printf_filtered ("RDI_step: %s\n", rdi_error_message (rslt));
    }
  else
    {
      char handle[4];
      CORE_ADDR pc = 0;

      if (step)
	{
	  pc = read_register (ARM_PC_REGNUM);
	  pc = arm_get_next_pc (pc);
	  arm_rdi_insert_breakpoint (pc, handle);
	}

      execute_status = rslt = angel_RDI_execute (&point);
      if (rslt != RDIError_NoError && rslt != RDIError_BreakpointReached)
	printf_filtered ("RDI_execute: %s\n", rdi_error_message (rslt));

      if (step)
	arm_rdi_remove_breakpoint (pc, handle);
    }
}