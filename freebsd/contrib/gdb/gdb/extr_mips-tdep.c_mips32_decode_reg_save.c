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

__attribute__((used)) static void
mips32_decode_reg_save (t_inst inst, unsigned long *gen_mask,
			unsigned long *float_mask)
{
  int reg;

  if ((inst & 0xffe00000) == 0xafa00000	/* sw reg,n($sp) */
      || (inst & 0xffe00000) == 0xafc00000	/* sw reg,n($r30) */
      || (inst & 0xffe00000) == 0xffa00000)	/* sd reg,n($sp) */
    {
      /* It might be possible to use the instruction to
         find the offset, rather than the code below which
         is based on things being in a certain order in the
         frame, but figuring out what the instruction's offset
         is relative to might be a little tricky.  */
      reg = (inst & 0x001f0000) >> 16;
      *gen_mask |= (1 << reg);
    }
  else if ((inst & 0xffe00000) == 0xe7a00000	/* swc1 freg,n($sp) */
	   || (inst & 0xffe00000) == 0xe7c00000	/* swc1 freg,n($r30) */
	   || (inst & 0xffe00000) == 0xf7a00000)	/* sdc1 freg,n($sp) */

    {
      reg = ((inst & 0x001f0000) >> 16);
      *float_mask |= (1 << reg);
    }
}