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
 int /*<<< orphan*/  alphabsd_supply_fpreg (char*,int) ; 
 int /*<<< orphan*/  alphabsd_supply_reg (char*,int) ; 
 scalar_t__ getregs_supplies (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fetch_inferior_registers (int regno)
{
  if (regno == -1 || getregs_supplies (regno))
    {
      struct reg gregs;

      if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &gregs, 0) == -1)
	perror_with_name ("Couldn't get registers");

      alphabsd_supply_reg ((char *) &gregs, regno);
      if (regno != -1)
	return;
    }

  if (regno == -1 || regno >= FP0_REGNUM)
    {
      struct fpreg fpregs;

      if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get floating point status");

      alphabsd_supply_fpreg ((char *) &fpregs, regno);
    }
}