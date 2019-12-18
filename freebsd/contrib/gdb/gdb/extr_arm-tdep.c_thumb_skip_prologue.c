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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 unsigned short read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
thumb_skip_prologue (CORE_ADDR pc, CORE_ADDR func_end)
{
  CORE_ADDR current_pc;
  /* findmask:
     bit 0 - push { rlist }
     bit 1 - mov r7, sp  OR  add r7, sp, #imm  (setting of r7)
     bit 2 - sub sp, #simm  OR  add sp, #simm  (adjusting of sp)
  */
  int findmask = 0;

  for (current_pc = pc;
       current_pc + 2 < func_end && current_pc < pc + 40;
       current_pc += 2)
    {
      unsigned short insn = read_memory_unsigned_integer (current_pc, 2);

      if ((insn & 0xfe00) == 0xb400)		/* push { rlist } */
	{
	  findmask |= 1;			/* push found */
	}
      else if ((insn & 0xff00) == 0xb000)	/* add sp, #simm  OR  
						   sub sp, #simm */
	{
	  if ((findmask & 1) == 0)		/* before push ? */
	    continue;
	  else
	    findmask |= 4;			/* add/sub sp found */
	}
      else if ((insn & 0xff00) == 0xaf00)	/* add r7, sp, #imm */
	{
	  findmask |= 2;			/* setting of r7 found */
	}
      else if (insn == 0x466f)			/* mov r7, sp */
	{
	  findmask |= 2;			/* setting of r7 found */
	}
      else if (findmask == (4+2+1))
	{
	  /* We have found one of each type of prologue instruction */
	  break;
	}
      else
	/* Something in the prolog that we don't care about or some
	   instruction from outside the prolog scheduled here for
	   optimization.  */
	continue;
    }

  return current_pc;
}