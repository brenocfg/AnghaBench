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
typedef  int t_inst ;

/* Variables and functions */
 int RA_REGNUM ; 
 int* mips16_to_32_reg ; 

__attribute__((used)) static void
mips16_decode_reg_save (t_inst inst, unsigned long *gen_mask)
{
  if ((inst & 0xf800) == 0xd000)	/* sw reg,n($sp) */
    {
      int reg = mips16_to_32_reg[(inst & 0x700) >> 8];
      *gen_mask |= (1 << reg);
    }
  else if ((inst & 0xff00) == 0xf900)	/* sd reg,n($sp) */
    {
      int reg = mips16_to_32_reg[(inst & 0xe0) >> 5];
      *gen_mask |= (1 << reg);
    }
  else if ((inst & 0xff00) == 0x6200	/* sw $ra,n($sp) */
	   || (inst & 0xff00) == 0xfa00)	/* sd $ra,n($sp) */
    *gen_mask |= (1 << RA_REGNUM);
}