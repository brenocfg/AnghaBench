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
 int AMD64_ST0_REGNUM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 int /*<<< orphan*/  amd64_collect_native_gregset (int /*<<< orphan*/ ,struct reg*,int) ; 
 int /*<<< orphan*/  amd64_fill_fxsave (char*,int) ; 
 scalar_t__ amd64_native_gregset_supplies_p (int) ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
store_inferior_registers (int regnum)
{
  if (regnum == -1 || amd64_native_gregset_supplies_p (regnum))
    {
      struct reg regs;

      if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
                  (PTRACE_ARG3_TYPE) &regs, 0) == -1)
        perror_with_name ("Couldn't get registers");

      amd64_collect_native_gregset (current_regcache, &regs, regnum);

      if (ptrace (PT_SETREGS, PIDGET (inferior_ptid),
	          (PTRACE_ARG3_TYPE) &regs, 0) == -1)
        perror_with_name ("Couldn't write registers");

      if (regnum != -1)
	return;
    }

  if (regnum == -1 || regnum >= AMD64_ST0_REGNUM)
    {
      struct fpreg fpregs;

      if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating point status");

      amd64_fill_fxsave ((char *) &fpregs, regnum);

      if (ptrace (PT_SETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't write floating point status");
    }
}