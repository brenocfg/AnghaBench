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
 int I387_ST0_REGNUM ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int i386_stab_reg_to_regnum (int) ; 

__attribute__((used)) static int
i386_dwarf_reg_to_regnum (int reg)
{
  /* The DWARF register numbering includes %eip and %eflags, and
     numbers the floating point registers differently.  */
  if (reg >= 0 && reg <= 9)
    {
      /* General-purpose registers.  */
      return reg;
    }
  else if (reg >= 11 && reg <= 18)
    {
      /* Floating-point registers.  */
      return reg - 11 + I387_ST0_REGNUM;
    }
  else if (reg >= 21)
    {
      /* The SSE and MMX registers have identical numbers as in stabs.  */
      return i386_stab_reg_to_regnum (reg);
    }

  /* This will hopefully provoke a warning.  */
  return NUM_REGS + NUM_PSEUDO_REGS;
}