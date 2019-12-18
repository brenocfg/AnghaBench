#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fp_control_status; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int itype_op (unsigned long) ; 
 int itype_rs (unsigned long) ; 
 int itype_rt (unsigned long) ; 
 int jtype_target (unsigned long) ; 
 scalar_t__ mips32_relative_offset (unsigned long) ; 
 unsigned long mips_fetch_instruction (int) ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int read_signed_register (int) ; 
 int rtype_funct (unsigned long) ; 
 int rtype_rs (unsigned long) ; 

__attribute__((used)) static CORE_ADDR
mips32_next_pc (CORE_ADDR pc)
{
  unsigned long inst;
  int op;
  inst = mips_fetch_instruction (pc);
  if ((inst & 0xe0000000) != 0)	/* Not a special, jump or branch instruction */
    {
      if (itype_op (inst) >> 2 == 5)
	/* BEQL, BNEL, BLEZL, BGTZL: bits 0101xx */
	{
	  op = (itype_op (inst) & 0x03);
	  switch (op)
	    {
	    case 0:		/* BEQL */
	      goto equal_branch;
	    case 1:		/* BNEL */
	      goto neq_branch;
	    case 2:		/* BLEZL */
	      goto less_branch;
	    case 3:		/* BGTZ */
	      goto greater_branch;
	    default:
	      pc += 4;
	    }
	}
      else if (itype_op (inst) == 17 && itype_rs (inst) == 8)
	/* BC1F, BC1FL, BC1T, BC1TL: 010001 01000 */
	{
	  int tf = itype_rt (inst) & 0x01;
	  int cnum = itype_rt (inst) >> 2;
	  int fcrcs =
	    read_signed_register (mips_regnum (current_gdbarch)->
				  fp_control_status);
	  int cond = ((fcrcs >> 24) & 0x0e) | ((fcrcs >> 23) & 0x01);

	  if (((cond >> cnum) & 0x01) == tf)
	    pc += mips32_relative_offset (inst) + 4;
	  else
	    pc += 8;
	}
      else
	pc += 4;		/* Not a branch, next instruction is easy */
    }
  else
    {				/* This gets way messy */

      /* Further subdivide into SPECIAL, REGIMM and other */
      switch (op = itype_op (inst) & 0x07)	/* extract bits 28,27,26 */
	{
	case 0:		/* SPECIAL */
	  op = rtype_funct (inst);
	  switch (op)
	    {
	    case 8:		/* JR */
	    case 9:		/* JALR */
	      /* Set PC to that address */
	      pc = read_signed_register (rtype_rs (inst));
	      break;
	    default:
	      pc += 4;
	    }

	  break;		/* end SPECIAL */
	case 1:		/* REGIMM */
	  {
	    op = itype_rt (inst);	/* branch condition */
	    switch (op)
	      {
	      case 0:		/* BLTZ */
	      case 2:		/* BLTZL */
	      case 16:		/* BLTZAL */
	      case 18:		/* BLTZALL */
	      less_branch:
		if (read_signed_register (itype_rs (inst)) < 0)
		  pc += mips32_relative_offset (inst) + 4;
		else
		  pc += 8;	/* after the delay slot */
		break;
	      case 1:		/* BGEZ */
	      case 3:		/* BGEZL */
	      case 17:		/* BGEZAL */
	      case 19:		/* BGEZALL */
		if (read_signed_register (itype_rs (inst)) >= 0)
		  pc += mips32_relative_offset (inst) + 4;
		else
		  pc += 8;	/* after the delay slot */
		break;
		/* All of the other instructions in the REGIMM category */
	      default:
		pc += 4;
	      }
	  }
	  break;		/* end REGIMM */
	case 2:		/* J */
	case 3:		/* JAL */
	  {
	    unsigned long reg;
	    reg = jtype_target (inst) << 2;
	    /* Upper four bits get never changed... */
	    pc = reg + ((pc + 4) & 0xf0000000);
	  }
	  break;
	  /* FIXME case JALX : */
	  {
	    unsigned long reg;
	    reg = jtype_target (inst) << 2;
	    pc = reg + ((pc + 4) & 0xf0000000) + 1;	/* yes, +1 */
	    /* Add 1 to indicate 16 bit mode - Invert ISA mode */
	  }
	  break;		/* The new PC will be alternate mode */
	case 4:		/* BEQ, BEQL */
	equal_branch:
	  if (read_signed_register (itype_rs (inst)) ==
	      read_signed_register (itype_rt (inst)))
	    pc += mips32_relative_offset (inst) + 4;
	  else
	    pc += 8;
	  break;
	case 5:		/* BNE, BNEL */
	neq_branch:
	  if (read_signed_register (itype_rs (inst)) !=
	      read_signed_register (itype_rt (inst)))
	    pc += mips32_relative_offset (inst) + 4;
	  else
	    pc += 8;
	  break;
	case 6:		/* BLEZ, BLEZL */
	  if (read_signed_register (itype_rs (inst) <= 0))
	    pc += mips32_relative_offset (inst) + 4;
	  else
	    pc += 8;
	  break;
	case 7:
	default:
	greater_branch:	/* BGTZ, BGTZL */
	  if (read_signed_register (itype_rs (inst) > 0))
	    pc += mips32_relative_offset (inst) + 4;
	  else
	    pc += 8;
	  break;
	}			/* switch */
    }				/* else */
  return pc;
}