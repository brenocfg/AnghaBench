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
 int FP0_REGNUM ; 
 scalar_t__ GETREGS_SUPPLIES (int) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_GETXMMREGS ; 
 int /*<<< orphan*/  current_regcache ; 
 int have_ptrace_xmmregs ; 
 int /*<<< orphan*/  i387_supply_fsave (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i387_supply_fxsave (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 

void
fetch_inferior_registers (int regno)
{
  if (regno == -1 || GETREGS_SUPPLIES (regno))
    {
      gregset_t gregs;

      if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &gregs, 0) == -1)
	perror_with_name ("Couldn't get registers");

      supply_gregset (&gregs);
      if (regno != -1)
	return;
    }

  if (regno == -1 || regno >= FP0_REGNUM)
    {
      fpregset_t fpregs;
#ifdef HAVE_PT_GETXMMREGS
      char xmmregs[512];

      if (have_ptrace_xmmregs != 0
	  && ptrace(PT_GETXMMREGS, PIDGET (inferior_ptid),
		    (PTRACE_ARG3_TYPE) xmmregs, 0) == 0)
	{
	  have_ptrace_xmmregs = 1;
	  i387_supply_fxsave (current_regcache, -1, xmmregs);
	}
      else
	{
          if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		      (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	    perror_with_name ("Couldn't get floating point status");

	  i387_supply_fsave (current_regcache, -1, &fpregs);
	}
#else
      if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating point status");

      i387_supply_fsave (current_regcache, -1, &fpregs);
#endif
    }
}