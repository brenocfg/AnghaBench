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
struct fpreg {int /*<<< orphan*/ * fpr; int /*<<< orphan*/  fpr_fpsr; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_F0_REGNUM ; 
#define  ARM_FPS_REGNUM 128 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int const,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static void
store_fp_register (int regno)
{
  struct fpreg inferior_fp_registers;
  int ret;

  ret = ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_fp_registers, 0);

  if (ret < 0)
    {
      warning ("unable to fetch floating-point registers");
      return;
    }

  switch (regno)
    {
    case ARM_FPS_REGNUM:
      regcache_collect (ARM_FPS_REGNUM,
			(char *) &inferior_fp_registers.fpr_fpsr);
      break;

    default:
      regcache_collect
	(regno, (char *) &inferior_fp_registers.fpr[regno - ARM_F0_REGNUM]);
      break;
    }

  ret = ptrace (PT_SETFPREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_fp_registers, 0);

  if (ret < 0)
    warning ("unable to write register %d to inferior", regno);
}