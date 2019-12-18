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
typedef  int LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 unsigned int alpha_read_insn (int) ; 
 int read_register (unsigned int) ; 

__attribute__((used)) static CORE_ADDR
alpha_next_pc (CORE_ADDR pc)
{
  unsigned int insn;
  unsigned int op;
  int offset;
  LONGEST rav;

  insn = alpha_read_insn (pc);

  /* Opcode is top 6 bits. */
  op = (insn >> 26) & 0x3f;

  if (op == 0x1a)
    {
      /* Jump format: target PC is:
	 RB & ~3  */
      return (read_register ((insn >> 16) & 0x1f) & ~3);
    }

  if ((op & 0x30) == 0x30)
    {
      /* Branch format: target PC is:
	 (new PC) + (4 * sext(displacement))  */
      if (op == 0x30 ||		/* BR */
	  op == 0x34)		/* BSR */
	{
 branch_taken:
          offset = (insn & 0x001fffff);
	  if (offset & 0x00100000)
	    offset  |= 0xffe00000;
	  offset *= 4;
	  return (pc + 4 + offset);
	}

      /* Need to determine if branch is taken; read RA.  */
      rav = (LONGEST) read_register ((insn >> 21) & 0x1f);
      switch (op)
	{
	case 0x38:		/* BLBC */
	  if ((rav & 1) == 0)
	    goto branch_taken;
	  break;
	case 0x3c:		/* BLBS */
	  if (rav & 1)
	    goto branch_taken;
	  break;
	case 0x39:		/* BEQ */
	  if (rav == 0)
	    goto branch_taken;
	  break;
	case 0x3d:		/* BNE */
	  if (rav != 0)
	    goto branch_taken;
	  break;
	case 0x3a:		/* BLT */
	  if (rav < 0)
	    goto branch_taken;
	  break;
	case 0x3b:		/* BLE */
	  if (rav <= 0)
	    goto branch_taken;
	  break;
	case 0x3f:		/* BGT */
	  if (rav > 0)
	    goto branch_taken;
	  break;
	case 0x3e:		/* BGE */
	  if (rav >= 0)
	    goto branch_taken;
	  break;

	/* ??? Missing floating-point branches.  */
	}
    }

  /* Not a branch or branch not taken; target PC is:
     pc + 4  */
  return (pc + 4);
}