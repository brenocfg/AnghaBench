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
typedef  int /*<<< orphan*/  gregset_t ;
typedef  int /*<<< orphan*/  fpregset_t ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 scalar_t__ FPREG_SUPPLIES (int) ; 
 scalar_t__ GREG_SUPPLIES (int) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 int /*<<< orphan*/  fill_fpregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
store_inferior_registers (int regno)
{
  union {
    fpregset_t fpr;
    gregset_t r;
  } regs;

  if (regno == -1 || GREG_SUPPLIES(regno))
    {
      if (ptrace (PT_GETREGS, PIDGET(inferior_ptid),
		  (PTRACE_ARG3_TYPE)&regs.r, 0) == -1)
	perror_with_name ("Couldn't get registers");
      fill_gregset (&regs.r, regno);
      if (ptrace (PT_SETREGS, PIDGET(inferior_ptid),
		  (PTRACE_ARG3_TYPE)&regs.r, 0) == -1)
	perror_with_name ("Couldn't get registers");
      if (regno != -1)
	return;
    }

  if (regno == -1 || FPREG_SUPPLIES(regno))
    {
      if (ptrace (PT_GETFPREGS, PIDGET(inferior_ptid),
		  (PTRACE_ARG3_TYPE)&regs.fpr, 0) == -1)
	perror_with_name ("Couldn't get FP registers");
      fill_fpregset (&regs.fpr, regno);
      if (ptrace (PT_SETFPREGS, PIDGET(inferior_ptid),
		  (PTRACE_ARG3_TYPE)&regs.fpr, 0) == -1)
	perror_with_name ("Couldn't get FP registers");
      if (regno != -1)
	return;
    }
}