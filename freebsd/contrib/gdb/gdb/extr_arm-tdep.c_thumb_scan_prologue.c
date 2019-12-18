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
struct symtab_and_line {scalar_t__ line; scalar_t__ end; } ;
struct arm_prologue_cache {int framesize; int frameoffset; size_t framereg; TYPE_1__* saved_regs; } ;
struct TYPE_2__ {int addr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int ARM_LR_REGNUM ; 
 int ARM_SP_REGNUM ; 
 size_t THUMB_FP_REGNUM ; 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 unsigned short read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static void
thumb_scan_prologue (CORE_ADDR prev_pc, struct arm_prologue_cache *cache)
{
  CORE_ADDR prologue_start;
  CORE_ADDR prologue_end;
  CORE_ADDR current_pc;
  /* Which register has been copied to register n?  */
  int saved_reg[16];
  /* findmask:
     bit 0 - push { rlist }
     bit 1 - mov r7, sp  OR  add r7, sp, #imm  (setting of r7)
     bit 2 - sub sp, #simm  OR  add sp, #simm  (adjusting of sp)
  */
  int findmask = 0;
  int i;

  if (find_pc_partial_function (prev_pc, NULL, &prologue_start, &prologue_end))
    {
      struct symtab_and_line sal = find_pc_line (prologue_start, 0);

      if (sal.line == 0)		/* no line info, use current PC  */
	prologue_end = prev_pc;
      else if (sal.end < prologue_end)	/* next line begins after fn end */
	prologue_end = sal.end;		/* (probably means no prologue)  */
    }
  else
    /* We're in the boondocks: allow for 
       16 pushes, an add, and "mv fp,sp".  */
    prologue_end = prologue_start + 40;

  prologue_end = min (prologue_end, prev_pc);

  /* Initialize the saved register map.  When register H is copied to
     register L, we will put H in saved_reg[L].  */
  for (i = 0; i < 16; i++)
    saved_reg[i] = i;

  /* Search the prologue looking for instructions that set up the
     frame pointer, adjust the stack pointer, and save registers.
     Do this until all basic prolog instructions are found.  */

  cache->framesize = 0;
  for (current_pc = prologue_start;
       (current_pc < prologue_end) && ((findmask & 7) != 7);
       current_pc += 2)
    {
      unsigned short insn;
      int regno;
      int offset;

      insn = read_memory_unsigned_integer (current_pc, 2);

      if ((insn & 0xfe00) == 0xb400)	/* push { rlist } */
	{
	  int mask;
	  findmask |= 1;		/* push found */
	  /* Bits 0-7 contain a mask for registers R0-R7.  Bit 8 says
	     whether to save LR (R14).  */
	  mask = (insn & 0xff) | ((insn & 0x100) << 6);

	  /* Calculate offsets of saved R0-R7 and LR.  */
	  for (regno = ARM_LR_REGNUM; regno >= 0; regno--)
	    if (mask & (1 << regno))
	      {
		cache->framesize += 4;
		cache->saved_regs[saved_reg[regno]].addr = -cache->framesize;
		/* Reset saved register map.  */
		saved_reg[regno] = regno;
	      }
	}
      else if ((insn & 0xff00) == 0xb000)	/* add sp, #simm  OR  
						   sub sp, #simm */
	{
	  if ((findmask & 1) == 0)		/* before push?  */
	    continue;
	  else
	    findmask |= 4;			/* add/sub sp found */
	  
	  offset = (insn & 0x7f) << 2;		/* get scaled offset */
	  if (insn & 0x80)		/* is it signed? (==subtracting) */
	    {
	      cache->frameoffset += offset;
	      offset = -offset;
	    }
	  cache->framesize -= offset;
	}
      else if ((insn & 0xff00) == 0xaf00)	/* add r7, sp, #imm */
	{
	  findmask |= 2;			/* setting of r7 found */
	  cache->framereg = THUMB_FP_REGNUM;
	  /* get scaled offset */
	  cache->frameoffset = (insn & 0xff) << 2;
	}
      else if (insn == 0x466f)			/* mov r7, sp */
	{
	  findmask |= 2;			/* setting of r7 found */
	  cache->framereg = THUMB_FP_REGNUM;
	  cache->frameoffset = 0;
	  saved_reg[THUMB_FP_REGNUM] = ARM_SP_REGNUM;
	}
      else if ((insn & 0xffc0) == 0x4640)	/* mov r0-r7, r8-r15 */
	{
	  int lo_reg = insn & 7;		/* dest.  register (r0-r7) */
	  int hi_reg = ((insn >> 3) & 7) + 8;	/* source register (r8-15) */
	  saved_reg[lo_reg] = hi_reg;		/* remember hi reg was saved */
	}
      else
	/* Something in the prolog that we don't care about or some
	   instruction from outside the prolog scheduled here for
	   optimization.  */ 
	continue;
    }
}