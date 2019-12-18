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
 int I387_MM0_REGNUM ; 
 int I387_ST0_REGNUM ; 
 int I387_XMM0_REGNUM ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 

__attribute__((used)) static int
i386_stab_reg_to_regnum (int reg)
{
  /* This implements what GCC calls the "default" register map.  */
  if (reg >= 0 && reg <= 7)
    {
      /* General-purpose registers.  */
      return reg;
    }
  else if (reg >= 12 && reg <= 19)
    {
      /* Floating-point registers.  */
      return reg - 12 + I387_ST0_REGNUM;
    }
  else if (reg >= 21 && reg <= 28)
    {
      /* SSE registers.  */
      return reg - 21 + I387_XMM0_REGNUM;
    }
  else if (reg >= 29 && reg <= 36)
    {
      /* MMX registers.  */
      return reg - 29 + I387_MM0_REGNUM;
    }

  /* This will hopefully provoke a warning.  */
  return NUM_REGS + NUM_PSEUDO_REGS;
}