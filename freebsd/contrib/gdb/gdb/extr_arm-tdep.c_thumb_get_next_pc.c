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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int ADDR_BITS_REMOVE (int) ; 
 int ARM_PS_REGNUM ; 
 int ARM_SP_REGNUM ; 
 unsigned long DEPRECATED_REGISTER_SIZE ; 
 unsigned long bitcount (int) ; 
 int bits (unsigned short,int,int) ; 
 scalar_t__ condition_true (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  error (char*) ; 
 unsigned short read_memory_integer (int,int) ; 
 void* read_register (int) ; 
 int sbits (unsigned short,int /*<<< orphan*/ ,int) ; 

CORE_ADDR
thumb_get_next_pc (CORE_ADDR pc)
{
  unsigned long pc_val = ((unsigned long) pc) + 4;	/* PC after prefetch */
  unsigned short inst1 = read_memory_integer (pc, 2);
  CORE_ADDR nextpc = pc + 2;		/* default is next instruction */
  unsigned long offset;

  if ((inst1 & 0xff00) == 0xbd00)	/* pop {rlist, pc} */
    {
      CORE_ADDR sp;

      /* Fetch the saved PC from the stack.  It's stored above
         all of the other registers.  */
      offset = bitcount (bits (inst1, 0, 7)) * DEPRECATED_REGISTER_SIZE;
      sp = read_register (ARM_SP_REGNUM);
      nextpc = (CORE_ADDR) read_memory_integer (sp + offset, 4);
      nextpc = ADDR_BITS_REMOVE (nextpc);
      if (nextpc == pc)
	error ("Infinite loop detected");
    }
  else if ((inst1 & 0xf000) == 0xd000)	/* conditional branch */
    {
      unsigned long status = read_register (ARM_PS_REGNUM);
      unsigned long cond = bits (inst1, 8, 11);
      if (cond != 0x0f && condition_true (cond, status))    /* 0x0f = SWI */
	nextpc = pc_val + (sbits (inst1, 0, 7) << 1);
    }
  else if ((inst1 & 0xf800) == 0xe000)	/* unconditional branch */
    {
      nextpc = pc_val + (sbits (inst1, 0, 10) << 1);
    }
  else if ((inst1 & 0xf800) == 0xf000)	/* long branch with link, and blx */
    {
      unsigned short inst2 = read_memory_integer (pc + 2, 2);
      offset = (sbits (inst1, 0, 10) << 12) + (bits (inst2, 0, 10) << 1);
      nextpc = pc_val + offset;
      /* For BLX make sure to clear the low bits.  */
      if (bits (inst2, 11, 12) == 1)
	nextpc = nextpc & 0xfffffffc;
    }
  else if ((inst1 & 0xff00) == 0x4700)	/* bx REG, blx REG */
    {
      if (bits (inst1, 3, 6) == 0x0f)
	nextpc = pc_val;
      else
	nextpc = read_register (bits (inst1, 3, 6));

      nextpc = ADDR_BITS_REMOVE (nextpc);
      if (nextpc == pc)
	error ("Infinite loop detected");
    }

  return nextpc;
}