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

/* Variables and functions */
 int ARM_PC_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int RDIError_NoError ; 
 int RDIReg_CPSR ; 
 int RDIReg_PC ; 
 int angel_RDI_CPUread (int,int,unsigned long*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,unsigned long) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
arm_rdi_fetch_registers (int regno)
{
  int rslt, rdi_regmask;
  unsigned long rawreg, rawregs[32];
  char cookedreg[4];

  if (regno == -1)
    {
      rslt = angel_RDI_CPUread (255, 0x27fff, rawregs);
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_CPUread: %s\n", rdi_error_message (rslt));
	}

      for (regno = 0; regno < 15; regno++)
	{
	  store_unsigned_integer (cookedreg, 4, rawregs[regno]);
	  supply_register (regno, (char *) cookedreg);
	}
      store_unsigned_integer (cookedreg, 4, rawregs[15]);
      supply_register (ARM_PS_REGNUM, (char *) cookedreg);
      arm_rdi_fetch_registers (ARM_PC_REGNUM);
    }
  else
    {
      if (regno == ARM_PC_REGNUM)
	rdi_regmask = RDIReg_PC;
      else if (regno == ARM_PS_REGNUM)
	rdi_regmask = RDIReg_CPSR;
      else if (regno < 0 || regno > 15)
	{
	  rawreg = 0;
	  supply_register (regno, (char *) &rawreg);
	  return;
	}
      else
	rdi_regmask = 1 << regno;

      rslt = angel_RDI_CPUread (255, rdi_regmask, &rawreg);
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_CPUread: %s\n", rdi_error_message (rslt));
	}
      store_unsigned_integer (cookedreg, 4, rawreg);
      supply_register (regno, (char *) cookedreg);
    }
}