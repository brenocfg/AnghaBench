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
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 scalar_t__ getfpregs_supplies (int) ; 
 scalar_t__ getregs_supplies (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ppcnbsd_supply_fpreg (char*,int) ; 
 int /*<<< orphan*/  ppcnbsd_supply_reg (char*,int) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fetch_inferior_registers (int regno)
{
  if (regno == -1 || getregs_supplies (regno))
    {
      struct reg regs;

      if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &regs, 0) == -1)
        perror_with_name ("Couldn't get registers");

      ppcnbsd_supply_reg ((char *) &regs, regno);
      if (regno != -1)
	return;
    }

  if (regno == -1 || getfpregs_supplies (regno))
    {
      struct fpreg fpregs;

      if (ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		  (PTRACE_ARG3_TYPE) &fpregs, 0) == -1)
	perror_with_name ("Couldn't get FP registers");

      ppcnbsd_supply_fpreg ((char *) &fpregs, regno);
      if (regno != -1)
	return;
    }
}