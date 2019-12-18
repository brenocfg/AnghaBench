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
struct reg {int /*<<< orphan*/ * r; int /*<<< orphan*/  r_pc; int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
#define  ARM_LR_REGNUM 131 
#define  ARM_PC_REGNUM 130 
#define  ARM_PS_REGNUM 129 
#define  ARM_SP_REGNUM 128 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  arm_apcs_32 ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_register (int const,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
fetch_register (int regno)
{
  struct reg inferior_registers;
  int ret;

  ret = ptrace (PT_GETREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_registers, 0);

  if (ret < 0)
    {
      warning ("unable to fetch general register");
      return;
    }

  switch (regno)
    {
    case ARM_SP_REGNUM:
      supply_register (ARM_SP_REGNUM, (char *) &inferior_registers.r_sp);
      break;

    case ARM_LR_REGNUM:
      supply_register (ARM_LR_REGNUM, (char *) &inferior_registers.r_lr);
      break;

    case ARM_PC_REGNUM:
      /* This is ok: we're running native... */
      inferior_registers.r_pc = ADDR_BITS_REMOVE (inferior_registers.r_pc);
      supply_register (ARM_PC_REGNUM, (char *) &inferior_registers.r_pc);
      break;

    case ARM_PS_REGNUM:
      if (arm_apcs_32)
	supply_register (ARM_PS_REGNUM, (char *) &inferior_registers.r_cpsr);
      else
	supply_register (ARM_PS_REGNUM, (char *) &inferior_registers.r_pc);
      break;

    default:
      supply_register (regno, (char *) &inferior_registers.r[regno]);
      break;
    }
}