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
 scalar_t__ alpha_after_prologue (scalar_t__) ; 
 unsigned long alpha_read_insn (scalar_t__) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static CORE_ADDR
alpha_skip_prologue (CORE_ADDR pc)
{
  unsigned long inst;
  int offset;
  CORE_ADDR post_prologue_pc;
  char buf[4];

  /* Silently return the unaltered pc upon memory errors.
     This could happen on OSF/1 if decode_line_1 tries to skip the
     prologue for quickstarted shared library functions when the
     shared library is not yet mapped in.
     Reading target memory is slow over serial lines, so we perform
     this check only if the target has shared libraries (which all
     Alpha targets do).  */
  if (target_read_memory (pc, buf, 4))
    return pc;

  /* See if we can determine the end of the prologue via the symbol table.
     If so, then return either PC, or the PC after the prologue, whichever
     is greater.  */

  post_prologue_pc = alpha_after_prologue (pc);
  if (post_prologue_pc != 0)
    return max (pc, post_prologue_pc);

  /* Can't determine prologue from the symbol table, need to examine
     instructions.  */

  /* Skip the typical prologue instructions. These are the stack adjustment
     instruction and the instructions that save registers on the stack
     or in the gcc frame.  */
  for (offset = 0; offset < 100; offset += 4)
    {
      inst = alpha_read_insn (pc + offset);

      if ((inst & 0xffff0000) == 0x27bb0000)	/* ldah $gp,n($t12) */
	continue;
      if ((inst & 0xffff0000) == 0x23bd0000)	/* lda $gp,n($gp) */
	continue;
      if ((inst & 0xffff0000) == 0x23de0000)	/* lda $sp,n($sp) */
	continue;
      if ((inst & 0xffe01fff) == 0x43c0153e)	/* subq $sp,n,$sp */
	continue;

      if (((inst & 0xfc1f0000) == 0xb41e0000		/* stq reg,n($sp) */
	   || (inst & 0xfc1f0000) == 0x9c1e0000)	/* stt reg,n($sp) */
	  && (inst & 0x03e00000) != 0x03e00000)		/* reg != $zero */
	continue;

      if (inst == 0x47de040f)			/* bis sp,sp,fp */
	continue;
      if (inst == 0x47fe040f)			/* bis zero,sp,fp */
	continue;

      break;
    }
  return pc + offset;
}