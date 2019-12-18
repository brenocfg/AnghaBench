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
 int MIPS16_INSTLEN ; 
 unsigned short mips_fetch_instruction (scalar_t__) ; 
 scalar_t__ skip_prologue_using_sal (scalar_t__) ; 

__attribute__((used)) static CORE_ADDR
mips16_skip_prologue (CORE_ADDR pc)
{
  CORE_ADDR end_pc;
  int extend_bytes = 0;
  int prev_extend_bytes;

  /* Table of instructions likely to be found in a function prologue.  */
  static struct
  {
    unsigned short inst;
    unsigned short mask;
  }
  table[] =
  {
    {
    0x6300, 0xff00}
    ,				/* addiu $sp,offset */
    {
    0xfb00, 0xff00}
    ,				/* daddiu $sp,offset */
    {
    0xd000, 0xf800}
    ,				/* sw reg,n($sp) */
    {
    0xf900, 0xff00}
    ,				/* sd reg,n($sp) */
    {
    0x6200, 0xff00}
    ,				/* sw $ra,n($sp) */
    {
    0xfa00, 0xff00}
    ,				/* sd $ra,n($sp) */
    {
    0x673d, 0xffff}
    ,				/* move $s1,sp */
    {
    0xd980, 0xff80}
    ,				/* sw $a0-$a3,n($s1) */
    {
    0x6704, 0xff1c}
    ,				/* move reg,$a0-$a3 */
    {
    0xe809, 0xf81f}
    ,				/* entry pseudo-op */
    {
    0x0100, 0xff00}
    ,				/* addiu $s1,$sp,n */
    {
    0, 0}			/* end of table marker */
  };

  /* Find an upper bound on the prologue.  */
  end_pc = skip_prologue_using_sal (pc);
  if (end_pc == 0)
    end_pc = pc + 100;		/* Magic.  */

  /* Skip the typical prologue instructions. These are the stack adjustment
     instruction and the instructions that save registers on the stack
     or in the gcc frame.  */
  for (; pc < end_pc; pc += MIPS16_INSTLEN)
    {
      unsigned short inst;
      int i;

      inst = mips_fetch_instruction (pc);

      /* Normally we ignore an extend instruction.  However, if it is
         not followed by a valid prologue instruction, we must adjust
         the pc back over the extend so that it won't be considered
         part of the prologue.  */
      if ((inst & 0xf800) == 0xf000)	/* extend */
	{
	  extend_bytes = MIPS16_INSTLEN;
	  continue;
	}
      prev_extend_bytes = extend_bytes;
      extend_bytes = 0;

      /* Check for other valid prologue instructions besides extend.  */
      for (i = 0; table[i].mask != 0; i++)
	if ((inst & table[i].mask) == table[i].inst)	/* found, get out */
	  break;
      if (table[i].mask != 0)	/* it was in table? */
	continue;		/* ignore it */
      else
	/* non-prologue */
	{
	  /* Return the current pc, adjusted backwards by 2 if
	     the previous instruction was an extend.  */
	  return pc - prev_extend_bytes;
	}
    }
  return pc;
}