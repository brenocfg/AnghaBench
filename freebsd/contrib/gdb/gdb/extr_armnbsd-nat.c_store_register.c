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
struct reg {unsigned int r_pc; int /*<<< orphan*/ * r; int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 unsigned int ADDR_BITS_REMOVE (unsigned int) ; 
#define  ARM_LR_REGNUM 131 
#define  ARM_PC_REGNUM 130 
#define  ARM_PS_REGNUM 129 
#define  ARM_SP_REGNUM 128 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 int /*<<< orphan*/  arm_apcs_32 ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int const,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static void
store_register (int regno)
{
  struct reg inferior_registers;
  int ret;

  ret = ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_registers, 0);

  if (ret < 0)
    {
      warning ("unable to fetch general registers");
      return;
    }

  switch (regno)
    {
    case ARM_SP_REGNUM:
      regcache_collect (ARM_SP_REGNUM, (char *) &inferior_registers.r_sp);
      break;

    case ARM_LR_REGNUM:
      regcache_collect (ARM_LR_REGNUM, (char *) &inferior_registers.r_lr);
      break;

    case ARM_PC_REGNUM:
      if (arm_apcs_32)
	regcache_collect (ARM_PC_REGNUM, (char *) &inferior_registers.r_pc);
      else
	{
	  unsigned pc_val;

	  regcache_collect (ARM_PC_REGNUM, (char *) &pc_val);
	  
	  pc_val = ADDR_BITS_REMOVE (pc_val);
	  inferior_registers.r_pc
	    ^= ADDR_BITS_REMOVE (inferior_registers.r_pc);
	  inferior_registers.r_pc |= pc_val;
	}
      break;

    case ARM_PS_REGNUM:
      if (arm_apcs_32)
	regcache_collect (ARM_PS_REGNUM, (char *) &inferior_registers.r_cpsr);
      else
	{
	  unsigned psr_val;

	  regcache_collect (ARM_PS_REGNUM, (char *) &psr_val);

	  psr_val ^= ADDR_BITS_REMOVE (psr_val);
	  inferior_registers.r_pc = ADDR_BITS_REMOVE (inferior_registers.r_pc);
	  inferior_registers.r_pc |= psr_val;
	}
      break;

    default:
      regcache_collect (regno, (char *) &inferior_registers.r[regno]);
      break;
    }

  ret = ptrace (PT_SETREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_registers, 0);

  if (ret < 0)
    warning ("unable to write register %d to inferior", regno);
}