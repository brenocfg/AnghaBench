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
 int FP0_REGNUM ; 
 int NTO_REG_FLOAT ; 
 int NTO_REG_GENERAL ; 
 int NUM_GPREGS ; 
 int X86_CPU_FXSR ; 
 int nto_cpuinfo_flags ; 
 scalar_t__ nto_cpuinfo_valid ; 
 unsigned int nto_reg_offset (int) ; 

__attribute__((used)) static int
i386nto_register_area (int regno, int regset, unsigned *off)
{
  int len;

  *off = 0;
  if (regset == NTO_REG_GENERAL)
    {
      if (regno == -1)
	return NUM_GPREGS * 4;

      *off = nto_reg_offset (regno);
      if (*off == -1)
	return 0;
      return 4;
    }
  else if (regset == NTO_REG_FLOAT)
    {
      unsigned off_adjust, regsize, regset_size;

      if (nto_cpuinfo_valid && nto_cpuinfo_flags | X86_CPU_FXSR)
	{
	  off_adjust = 32;
	  regsize = 16;
	  regset_size = 512;
	}
      else
	{
	  off_adjust = 28;
	  regsize = 10;
	  regset_size = 128;
	}

      if (regno == -1)
	return regset_size;

      *off = (regno - FP0_REGNUM) * regsize + off_adjust;
      return 10;
      /* Why 10 instead of regsize?  GDB only stores 10 bytes per FP
         register so if we're sending a register back to the target,
         we only want pdebug to write 10 bytes so as not to clobber
         the reserved 6 bytes in the fxsave structure.  */
    }
  return -1;
}