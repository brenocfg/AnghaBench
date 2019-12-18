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
struct upk_mips16 {int offset; int regx; unsigned int regy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int add_offset_16 (int,int) ; 
 unsigned int fetch_mips_16 (int) ; 
 int /*<<< orphan*/  i8type ; 
 int /*<<< orphan*/  itype ; 
 int /*<<< orphan*/  jalxtype ; 
 int read_signed_register (int) ; 
 int /*<<< orphan*/  ritype ; 
 int /*<<< orphan*/  unpack_mips16 (int,unsigned int,unsigned int,int /*<<< orphan*/ ,struct upk_mips16*) ; 

__attribute__((used)) static CORE_ADDR
extended_mips16_next_pc (CORE_ADDR pc,
			 unsigned int extension, unsigned int insn)
{
  int op = (insn >> 11);
  switch (op)
    {
    case 2:			/* Branch */
      {
	CORE_ADDR offset;
	struct upk_mips16 upk;
	unpack_mips16 (pc, extension, insn, itype, &upk);
	offset = upk.offset;
	if (offset & 0x800)
	  {
	    offset &= 0xeff;
	    offset = -offset;
	  }
	pc += (offset << 1) + 2;
	break;
      }
    case 3:			/* JAL , JALX - Watch out, these are 32 bit instruction */
      {
	struct upk_mips16 upk;
	unpack_mips16 (pc, extension, insn, jalxtype, &upk);
	pc = add_offset_16 (pc, upk.offset);
	if ((insn >> 10) & 0x01)	/* Exchange mode */
	  pc = pc & ~0x01;	/* Clear low bit, indicate 32 bit mode */
	else
	  pc |= 0x01;
	break;
      }
    case 4:			/* beqz */
      {
	struct upk_mips16 upk;
	int reg;
	unpack_mips16 (pc, extension, insn, ritype, &upk);
	reg = read_signed_register (upk.regx);
	if (reg == 0)
	  pc += (upk.offset << 1) + 2;
	else
	  pc += 2;
	break;
      }
    case 5:			/* bnez */
      {
	struct upk_mips16 upk;
	int reg;
	unpack_mips16 (pc, extension, insn, ritype, &upk);
	reg = read_signed_register (upk.regx);
	if (reg != 0)
	  pc += (upk.offset << 1) + 2;
	else
	  pc += 2;
	break;
      }
    case 12:			/* I8 Formats btez btnez */
      {
	struct upk_mips16 upk;
	int reg;
	unpack_mips16 (pc, extension, insn, i8type, &upk);
	/* upk.regx contains the opcode */
	reg = read_signed_register (24);	/* Test register is 24 */
	if (((upk.regx == 0) && (reg == 0))	/* BTEZ */
	    || ((upk.regx == 1) && (reg != 0)))	/* BTNEZ */
	  /* pc = add_offset_16(pc,upk.offset) ; */
	  pc += (upk.offset << 1) + 2;
	else
	  pc += 2;
	break;
      }
    case 29:			/* RR Formats JR, JALR, JALR-RA */
      {
	struct upk_mips16 upk;
	/* upk.fmt = rrtype; */
	op = insn & 0x1f;
	if (op == 0)
	  {
	    int reg;
	    upk.regx = (insn >> 8) & 0x07;
	    upk.regy = (insn >> 5) & 0x07;
	    switch (upk.regy)
	      {
	      case 0:
		reg = upk.regx;
		break;
	      case 1:
		reg = 31;
		break;		/* Function return instruction */
	      case 2:
		reg = upk.regx;
		break;
	      default:
		reg = 31;
		break;		/* BOGUS Guess */
	      }
	    pc = read_signed_register (reg);
	  }
	else
	  pc += 2;
	break;
      }
    case 30:
      /* This is an instruction extension.  Fetch the real instruction
         (which follows the extension) and decode things based on
         that. */
      {
	pc += 2;
	pc = extended_mips16_next_pc (pc, insn, fetch_mips_16 (pc));
	break;
      }
    default:
      {
	pc += 2;
	break;
      }
    }
  return pc;
}