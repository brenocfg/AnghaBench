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
 int NUM_REGS ; 
 int RDIError_NoError ; 
 int RDIReg_CPSR ; 
 int RDIReg_PC ; 
 int angel_RDI_CPUwrite (int,int,unsigned long*) ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 int /*<<< orphan*/  store_unsigned_integer (unsigned long*,int,unsigned long) ; 

__attribute__((used)) static void
arm_rdi_store_registers (int regno)
{
  int rslt, rdi_regmask;

  /* These need to be able to take 'floating point register' contents */
  unsigned long rawreg[3], rawerreg[3];

  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	arm_rdi_store_registers (regno);
    }
  else
    {
      deprecated_read_register_gen (regno, (char *) rawreg);
      /* RDI manipulates data in host byte order, so convert now. */
      store_unsigned_integer (rawerreg, 4, rawreg[0]);

      if (regno == ARM_PC_REGNUM)
	rdi_regmask = RDIReg_PC;
      else if (regno == ARM_PS_REGNUM)
	rdi_regmask = RDIReg_CPSR;
      else if (regno < 0 || regno > 15)
	return;
      else
	rdi_regmask = 1 << regno;

      rslt = angel_RDI_CPUwrite (255, rdi_regmask, rawerreg);
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_CPUwrite: %s\n", rdi_error_message (rslt));
	}
    }
}