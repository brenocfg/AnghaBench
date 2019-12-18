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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ MIPS_INSTLEN ; 
 int mips_fetch_instruction (scalar_t__) ; 
 scalar_t__ skip_prologue_using_sal (scalar_t__) ; 

__attribute__((used)) static CORE_ADDR
mips32_skip_prologue (CORE_ADDR pc)
{
  t_inst inst;
  CORE_ADDR end_pc;
  int seen_sp_adjust = 0;
  int load_immediate_bytes = 0;

  /* Find an upper bound on the prologue.  */
  end_pc = skip_prologue_using_sal (pc);
  if (end_pc == 0)
    end_pc = pc + 100;		/* Magic.  */

  /* Skip the typical prologue instructions. These are the stack adjustment
     instruction and the instructions that save registers on the stack
     or in the gcc frame.  */
  for (; pc < end_pc; pc += MIPS_INSTLEN)
    {
      unsigned long high_word;

      inst = mips_fetch_instruction (pc);
      high_word = (inst >> 16) & 0xffff;

      if (high_word == 0x27bd	/* addiu $sp,$sp,offset */
	  || high_word == 0x67bd)	/* daddiu $sp,$sp,offset */
	seen_sp_adjust = 1;
      else if (inst == 0x03a1e823 ||	/* subu $sp,$sp,$at */
	       inst == 0x03a8e823)	/* subu $sp,$sp,$t0 */
	seen_sp_adjust = 1;
      else if (((inst & 0xFFE00000) == 0xAFA00000	/* sw reg,n($sp) */
		|| (inst & 0xFFE00000) == 0xFFA00000)	/* sd reg,n($sp) */
	       && (inst & 0x001F0000))	/* reg != $zero */
	continue;

      else if ((inst & 0xFFE00000) == 0xE7A00000)	/* swc1 freg,n($sp) */
	continue;
      else if ((inst & 0xF3E00000) == 0xA3C00000 && (inst & 0x001F0000))
	/* sx reg,n($s8) */
	continue;		/* reg != $zero */

      /* move $s8,$sp.  With different versions of gas this will be either
         `addu $s8,$sp,$zero' or `or $s8,$sp,$zero' or `daddu s8,sp,$0'.
         Accept any one of these.  */
      else if (inst == 0x03A0F021 || inst == 0x03a0f025 || inst == 0x03a0f02d)
	continue;

      else if ((inst & 0xFF9F07FF) == 0x00800021)	/* move reg,$a0-$a3 */
	continue;
      else if (high_word == 0x3c1c)	/* lui $gp,n */
	continue;
      else if (high_word == 0x279c)	/* addiu $gp,$gp,n */
	continue;
      else if (inst == 0x0399e021	/* addu $gp,$gp,$t9 */
	       || inst == 0x033ce021)	/* addu $gp,$t9,$gp */
	continue;
      /* The following instructions load $at or $t0 with an immediate
         value in preparation for a stack adjustment via
         subu $sp,$sp,[$at,$t0]. These instructions could also initialize
         a local variable, so we accept them only before a stack adjustment
         instruction was seen.  */
      else if (!seen_sp_adjust)
	{
	  if (high_word == 0x3c01 ||	/* lui $at,n */
	      high_word == 0x3c08)	/* lui $t0,n */
	    {
	      load_immediate_bytes += MIPS_INSTLEN;	/* FIXME!! */
	      continue;
	    }
	  else if (high_word == 0x3421 ||	/* ori $at,$at,n */
		   high_word == 0x3508 ||	/* ori $t0,$t0,n */
		   high_word == 0x3401 ||	/* ori $at,$zero,n */
		   high_word == 0x3408)	/* ori $t0,$zero,n */
	    {
	      load_immediate_bytes += MIPS_INSTLEN;	/* FIXME!! */
	      continue;
	    }
	  else
	    break;
	}
      else
	break;
    }

  /* In a frameless function, we might have incorrectly
     skipped some load immediate instructions. Undo the skipping
     if the load immediate was not followed by a stack adjustment.  */
  if (load_immediate_bytes && !seen_sp_adjust)
    pc -= load_immediate_bytes;
  return pc;
}