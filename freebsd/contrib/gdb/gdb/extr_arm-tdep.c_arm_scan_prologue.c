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
struct frame_info {int dummy; } ;
struct arm_prologue_cache {scalar_t__ framereg; int framesize; int frameoffset; TYPE_1__* saved_regs; } ;
struct TYPE_2__ {int addr; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
 unsigned int ARM_F0_REGNUM ; 
 scalar_t__ ARM_FP_REGNUM ; 
 size_t ARM_LR_REGNUM ; 
 int ARM_PC_REGNUM ; 
 scalar_t__ ARM_SP_REGNUM ; 
 scalar_t__ arm_pc_is_thumb (scalar_t__) ; 
 scalar_t__ find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  frame_tdep_pc_fixup (scalar_t__*) ; 
 scalar_t__ frame_unwind_register_unsigned (struct frame_info*,scalar_t__) ; 
 unsigned int read_memory_unsigned_integer (scalar_t__,int) ; 
 int /*<<< orphan*/  safe_read_memory_integer (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thumb_scan_prologue (scalar_t__,struct arm_prologue_cache*) ; 

__attribute__((used)) static void
arm_scan_prologue (struct frame_info *next_frame, struct arm_prologue_cache *cache)
{
  int regno, sp_offset, fp_offset, ip_offset;
  CORE_ADDR prologue_start, prologue_end, current_pc;
  CORE_ADDR prev_pc = frame_pc_unwind (next_frame);

  /* Assume there is no frame until proven otherwise.  */
  cache->framereg = ARM_SP_REGNUM;
  cache->framesize = 0;
  cache->frameoffset = 0;

  if (frame_tdep_pc_fixup)
  	frame_tdep_pc_fixup(&prev_pc);

  /* Check for Thumb prologue.  */
  if (arm_pc_is_thumb (prev_pc))
    {
      thumb_scan_prologue (prev_pc, cache);
      return;
    }

  /* Find the function prologue.  If we can't find the function in
     the symbol table, peek in the stack frame to find the PC.  */
  if (find_pc_partial_function (prev_pc, NULL, &prologue_start, &prologue_end))
    {
      /* One way to find the end of the prologue (which works well
         for unoptimized code) is to do the following:

	    struct symtab_and_line sal = find_pc_line (prologue_start, 0);

	    if (sal.line == 0)
	      prologue_end = prev_pc;
	    else if (sal.end < prologue_end)
	      prologue_end = sal.end;

	 This mechanism is very accurate so long as the optimizer
	 doesn't move any instructions from the function body into the
	 prologue.  If this happens, sal.end will be the last
	 instruction in the first hunk of prologue code just before
	 the first instruction that the scheduler has moved from
	 the body to the prologue.

	 In order to make sure that we scan all of the prologue
	 instructions, we use a slightly less accurate mechanism which
	 may scan more than necessary.  To help compensate for this
	 lack of accuracy, the prologue scanning loop below contains
	 several clauses which'll cause the loop to terminate early if
	 an implausible prologue instruction is encountered.  
	 
	 The expression
	 
	      prologue_start + 64
	    
	 is a suitable endpoint since it accounts for the largest
	 possible prologue plus up to five instructions inserted by
	 the scheduler.  */
         
      if (prologue_end > prologue_start + 64)
	{
	  prologue_end = prologue_start + 64;	/* See above.  */
	}
    }
  else
    {
      /* We have no symbol information.  Our only option is to assume this
	 function has a standard stack frame and the normal frame register.
	 Then, we can find the value of our frame pointer on entrance to
	 the callee (or at the present moment if this is the innermost frame).
	 The value stored there should be the address of the stmfd + 8.  */
      CORE_ADDR frame_loc;
      LONGEST return_value;

      frame_loc = frame_unwind_register_unsigned (next_frame, ARM_FP_REGNUM);
      if (!safe_read_memory_integer (frame_loc, 4, &return_value))
        return;
      else
        {
          prologue_start = ADDR_BITS_REMOVE (return_value) - 8;
          prologue_end = prologue_start + 64;	/* See above.  */
        }
    }

  if (prev_pc < prologue_end)
    prologue_end = prev_pc;

  /* Now search the prologue looking for instructions that set up the
     frame pointer, adjust the stack pointer, and save registers.

     Be careful, however, and if it doesn't look like a prologue,
     don't try to scan it.  If, for instance, a frameless function
     begins with stmfd sp!, then we will tell ourselves there is
     a frame, which will confuse stack traceback, as well as "finish" 
     and other operations that rely on a knowledge of the stack
     traceback.

     In the APCS, the prologue should start with  "mov ip, sp" so
     if we don't see this as the first insn, we will stop.  

     [Note: This doesn't seem to be true any longer, so it's now an
     optional part of the prologue.  - Kevin Buettner, 2001-11-20]

     [Note further: The "mov ip,sp" only seems to be missing in
     frameless functions at optimization level "-O2" or above,
     in which case it is often (but not always) replaced by
     "str lr, [sp, #-4]!".  - Michael Snyder, 2002-04-23]  */

  sp_offset = fp_offset = ip_offset = 0;

  for (current_pc = prologue_start;
       current_pc < prologue_end;
       current_pc += 4)
    {
      unsigned int insn = read_memory_unsigned_integer (current_pc, 4);

      if (insn == 0xe1a0c00d)		/* mov ip, sp */
	{
	  ip_offset = 0;
	  continue;
	}
      else if ((insn & 0xfffff000) == 0xe28dc000) /* add ip, sp #n */
	{
	  unsigned imm = insn & 0xff;                   /* immediate value */
	  unsigned rot = (insn & 0xf00) >> 7;           /* rotate amount */
	  imm = (imm >> rot) | (imm << (32 - rot));
	  ip_offset = imm;
	  continue;
	}
      else if ((insn & 0xfffff000) == 0xe24dc000) /* sub ip, sp #n */
	{
	  unsigned imm = insn & 0xff;                   /* immediate value */
	  unsigned rot = (insn & 0xf00) >> 7;           /* rotate amount */
	  imm = (imm >> rot) | (imm << (32 - rot));
	  ip_offset = -imm;
	  continue;
	}
      else if (insn == 0xe52de004)	/* str lr, [sp, #-4]! */
	{
	  sp_offset -= 4;
	  cache->saved_regs[ARM_LR_REGNUM].addr = sp_offset;
	  continue;
	}
      else if ((insn & 0xffff0000) == 0xe92d0000)
	/* stmfd sp!, {..., fp, ip, lr, pc}
	   or
	   stmfd sp!, {a1, a2, a3, a4}  */
	{
	  int mask = insn & 0xffff;

	  /* Calculate offsets of saved registers.  */
	  for (regno = ARM_PC_REGNUM; regno >= 0; regno--)
	    if (mask & (1 << regno))
	      {
		sp_offset -= 4;
		cache->saved_regs[regno].addr = sp_offset;
	      }
	}
      else if ((insn & 0xffffc000) == 0xe54b0000 ||	/* strb rx,[r11,#-n] */
	       (insn & 0xffffc0f0) == 0xe14b00b0 ||	/* strh rx,[r11,#-n] */
	       (insn & 0xffffc000) == 0xe50b0000)	/* str  rx,[r11,#-n] */
	{
	  /* No need to add this to saved_regs -- it's just an arg reg.  */
	  continue;
	}
      else if ((insn & 0xffffc000) == 0xe5cd0000 ||	/* strb rx,[sp,#n] */
	       (insn & 0xffffc0f0) == 0xe1cd00b0 ||	/* strh rx,[sp,#n] */
	       (insn & 0xffffc000) == 0xe58d0000)	/* str  rx,[sp,#n] */
	{
	  /* No need to add this to saved_regs -- it's just an arg reg.  */
	  continue;
	}
      else if ((insn & 0xfffff000) == 0xe24cb000)	/* sub fp, ip #n */
	{
	  unsigned imm = insn & 0xff;			/* immediate value */
	  unsigned rot = (insn & 0xf00) >> 7;		/* rotate amount */
	  imm = (imm >> rot) | (imm << (32 - rot));
	  fp_offset = -imm + ip_offset;
	  cache->framereg = ARM_FP_REGNUM;
	}
      else if ((insn & 0xfffff000) == 0xe24dd000)	/* sub sp, sp #n */
	{
	  unsigned imm = insn & 0xff;			/* immediate value */
	  unsigned rot = (insn & 0xf00) >> 7;		/* rotate amount */
	  imm = (imm >> rot) | (imm << (32 - rot));
	  sp_offset -= imm;
	}
      else if ((insn & 0xffff7fff) == 0xed6d0103)	/* stfe f?, [sp, -#c]! */
	{
	  sp_offset -= 12;
	  regno = ARM_F0_REGNUM + ((insn >> 12) & 0x07);
	  cache->saved_regs[regno].addr = sp_offset;
	}
      else if ((insn & 0xffbf0fff) == 0xec2d0200)	/* sfmfd f0, 4, [sp!] */
	{
	  int n_saved_fp_regs;
	  unsigned int fp_start_reg, fp_bound_reg;

	  if ((insn & 0x800) == 0x800)		/* N0 is set */
	    {
	      if ((insn & 0x40000) == 0x40000)	/* N1 is set */
		n_saved_fp_regs = 3;
	      else
		n_saved_fp_regs = 1;
	    }
	  else
	    {
	      if ((insn & 0x40000) == 0x40000)	/* N1 is set */
		n_saved_fp_regs = 2;
	      else
		n_saved_fp_regs = 4;
	    }

	  fp_start_reg = ARM_F0_REGNUM + ((insn >> 12) & 0x7);
	  fp_bound_reg = fp_start_reg + n_saved_fp_regs;
	  for (; fp_start_reg < fp_bound_reg; fp_start_reg++)
	    {
	      sp_offset -= 12;
	      cache->saved_regs[fp_start_reg++].addr = sp_offset;
	    }
	}
      else if ((insn & 0xf0000000) != 0xe0000000)
	break;			/* Condition not true, exit early */
      else if ((insn & 0xfe200000) == 0xe8200000)	/* ldm? */
	break;			/* Don't scan past a block load */
      else
	/* The optimizer might shove anything into the prologue,
	   so we just skip what we don't recognize.  */
	continue;
    }

  /* The frame size is just the negative of the offset (from the
     original SP) of the last thing thing we pushed on the stack. 
     The frame offset is [new FP] - [new SP].  */
  cache->framesize = -sp_offset;
  if (cache->framereg == ARM_FP_REGNUM)
    cache->frameoffset = fp_offset - sp_offset;
  else
    cache->frameoffset = 0;
}