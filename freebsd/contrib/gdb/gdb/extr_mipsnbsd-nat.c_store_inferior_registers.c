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
struct reg {int dummy; } ;
struct fpreg {int dummy; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int FP0_REGNUM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 scalar_t__ getregs_supplies (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  mipsnbsd_fill_fpreg (char*,int) ; 
 int /*<<< orphan*/  mipsnbsd_fill_reg (char*,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
store_inferior_registers (int regno)
{
  if (regno == -1 || getregs_supplies (regno))
    {
      struct reg regs;

      if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &regs, 0) == -1)
	perror_with_name ("Couldn't get registers");

      mipsnbsd_fill_reg ((char *) &regs, regno);

      if (ptrace (PT_SETREGS, PIDGET (inferior_ptid), 
		  (PTRACE_ARG3_TYPE) &regs, 0) == -1)
	perror_with_name ("Couldn't write registers");

      if (regno != -1)
	return;
    }

  if (regno == -1 || regno >= FP0_REGNUM)
    {
      struct fpreg fpregs; 

      if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating point status");

      mipsnbsd_fill_fpreg ((char *) &fpregs, regno);

      if (ptrace (PT_SETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't write floating point status");
    }
}