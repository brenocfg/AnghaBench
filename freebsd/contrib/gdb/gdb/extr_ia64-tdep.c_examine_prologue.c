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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tmp ;
struct ia64_frame_cache {scalar_t__ after_prologue; int cfm; scalar_t__* saved_regs; scalar_t__ sor; scalar_t__ sof; scalar_t__ sol; scalar_t__ bsp; int frameless; int mem_stack_frame_size; int fp_reg; scalar_t__ prev_cfm; } ;
struct frame_info {int dummy; } ;
typedef  scalar_t__ instruction_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ B ; 
 scalar_t__ I ; 
 size_t IA64_CFM_REGNUM ; 
 int IA64_FR0_REGNUM ; 
 int IA64_GR0_REGNUM ; 
 int IA64_GR32_REGNUM ; 
 size_t IA64_PR_REGNUM ; 
 size_t IA64_UNAT_REGNUM ; 
 size_t IA64_VFP_REGNUM ; 
 size_t IA64_VRAP_REGNUM ; 
 scalar_t__ IS_NaT_COLLECTION_ADDR (scalar_t__) ; 
 scalar_t__ M ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ extract_unsigned_integer (char*,int) ; 
 scalar_t__ fetch_instruction (scalar_t__,scalar_t__*,long long*) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  ia64_read_reg (scalar_t__,scalar_t__*,int) ; 
 int imm9 (long long) ; 
 scalar_t__ isScratch (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ refine_prologue_limit (scalar_t__,scalar_t__,int*) ; 
 scalar_t__ rse_address_add (scalar_t__,scalar_t__) ; 
 int sp_regnum ; 

__attribute__((used)) static CORE_ADDR
examine_prologue (CORE_ADDR pc, CORE_ADDR lim_pc, struct frame_info *next_frame, struct ia64_frame_cache *cache)
{
  CORE_ADDR next_pc;
  CORE_ADDR last_prologue_pc = pc;
  instruction_type it;
  long long instr;
  int cfm_reg  = 0;
  int ret_reg  = 0;
  int fp_reg   = 0;
  int unat_save_reg = 0;
  int pr_save_reg = 0;
  int mem_stack_frame_size = 0;
  int spill_reg   = 0;
  CORE_ADDR spill_addr = 0;
  char instores[8];
  char infpstores[8];
  char reg_contents[256];
  int trust_limit;
  int frameless = 1;
  int i;
  CORE_ADDR addr;
  char buf[8];
  CORE_ADDR bof, sor, sol, sof, cfm, rrb_gr;

  memset (instores, 0, sizeof instores);
  memset (infpstores, 0, sizeof infpstores);
  memset (reg_contents, 0, sizeof reg_contents);

  if (cache->after_prologue != 0
      && cache->after_prologue <= lim_pc)
    return cache->after_prologue;

  lim_pc = refine_prologue_limit (pc, lim_pc, &trust_limit);
  next_pc = fetch_instruction (pc, &it, &instr);

  /* We want to check if we have a recognizable function start before we
     look ahead for a prologue.  */
  if (pc < lim_pc && next_pc 
      && it == M && ((instr & 0x1ee0000003fLL) == 0x02c00000000LL))
    {
      /* alloc - start of a regular function.  */
      int sor = (int) ((instr & 0x00078000000LL) >> 27);
      int sol = (int) ((instr & 0x00007f00000LL) >> 20);
      int sof = (int) ((instr & 0x000000fe000LL) >> 13);
      int rN = (int) ((instr & 0x00000001fc0LL) >> 6);

      /* Verify that the current cfm matches what we think is the
	 function start.  If we have somehow jumped within a function,
	 we do not want to interpret the prologue and calculate the
	 addresses of various registers such as the return address.  
	 We will instead treat the frame as frameless. */
      if (!next_frame ||
	  (sof == (cache->cfm & 0x7f) &&
	   sol == ((cache->cfm >> 7) & 0x7f)))
	frameless = 0;

      cfm_reg = rN;
      last_prologue_pc = next_pc;
      pc = next_pc;
    }
  else
    {
      /* Look for a leaf routine.  */
      if (pc < lim_pc && next_pc
	  && (it == I || it == M) 
          && ((instr & 0x1ee00000000LL) == 0x10800000000LL))
	{
	  /* adds rN = imm14, rM   (or mov rN, rM  when imm14 is 0) */
	  int imm = (int) ((((instr & 0x01000000000LL) ? -1 : 0) << 13) 
	                   | ((instr & 0x001f8000000LL) >> 20)
		           | ((instr & 0x000000fe000LL) >> 13));
	  int rM = (int) ((instr & 0x00007f00000LL) >> 20);
	  int rN = (int) ((instr & 0x00000001fc0LL) >> 6);
	  int qp = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && rN == 2 && imm == 0 && rM == 12 && fp_reg == 0)
	    {
	      /* mov r2, r12 - beginning of leaf routine */
	      fp_reg = rN;
	      last_prologue_pc = next_pc;
	    }
	} 

      /* If we don't recognize a regular function or leaf routine, we are
	 done.  */
      if (!fp_reg)
	{
	  pc = lim_pc;	
	  if (trust_limit)
	    last_prologue_pc = lim_pc;
	}
    }

  /* Loop, looking for prologue instructions, keeping track of
     where preserved registers were spilled. */
  while (pc < lim_pc)
    {
      next_pc = fetch_instruction (pc, &it, &instr);
      if (next_pc == 0)
	break;

      if (it == B && ((instr & 0x1e1f800003f) != 0x04000000000))
	{
	  /* Exit loop upon hitting a non-nop branch instruction. */ 
	  if (trust_limit)
	    lim_pc = pc;
	  break;
	}
      else if (((instr & 0x3fLL) != 0LL) && 
	       (frameless || ret_reg != 0))
	{
	  /* Exit loop upon hitting a predicated instruction if
	     we already have the return register or if we are frameless.  */ 
	  if (trust_limit)
	    lim_pc = pc;
	  break;
	}
      else if (it == I && ((instr & 0x1eff8000000LL) == 0x00188000000LL))
        {
	  /* Move from BR */
	  int b2 = (int) ((instr & 0x0000000e000LL) >> 13);
	  int rN = (int) ((instr & 0x00000001fc0LL) >> 6);
	  int qp = (int) (instr & 0x0000000003f);

	  if (qp == 0 && b2 == 0 && rN >= 32 && ret_reg == 0)
	    {
	      ret_reg = rN;
	      last_prologue_pc = next_pc;
	    }
	}
      else if ((it == I || it == M) 
          && ((instr & 0x1ee00000000LL) == 0x10800000000LL))
	{
	  /* adds rN = imm14, rM   (or mov rN, rM  when imm14 is 0) */
	  int imm = (int) ((((instr & 0x01000000000LL) ? -1 : 0) << 13) 
	                   | ((instr & 0x001f8000000LL) >> 20)
		           | ((instr & 0x000000fe000LL) >> 13));
	  int rM = (int) ((instr & 0x00007f00000LL) >> 20);
	  int rN = (int) ((instr & 0x00000001fc0LL) >> 6);
	  int qp = (int) (instr & 0x0000000003fLL);

	  if (qp == 0 && rN >= 32 && imm == 0 && rM == 12 && fp_reg == 0)
	    {
	      /* mov rN, r12 */
	      fp_reg = rN;
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && rN == 12 && rM == 12)
	    {
	      /* adds r12, -mem_stack_frame_size, r12 */
	      mem_stack_frame_size -= imm;
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && rN == 2 
	        && ((rM == fp_reg && fp_reg != 0) || rM == 12))
	    {
	      char buf[MAX_REGISTER_SIZE];
	      CORE_ADDR saved_sp = 0;
	      /* adds r2, spilloffset, rFramePointer 
	           or
		 adds r2, spilloffset, r12

	         Get ready for stf.spill or st8.spill instructions.
		 The address to start spilling at is loaded into r2. 
		 FIXME:  Why r2?  That's what gcc currently uses; it
		 could well be different for other compilers.  */

	      /* Hmm... whether or not this will work will depend on
	         where the pc is.  If it's still early in the prologue
		 this'll be wrong.  FIXME */
	      if (next_frame)
		{
		  frame_unwind_register (next_frame, sp_regnum, buf);
		  saved_sp = extract_unsigned_integer (buf, 8);
		}
	      spill_addr  = saved_sp
	                  + (rM == 12 ? 0 : mem_stack_frame_size) 
			  + imm;
	      spill_reg   = rN;
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && rM >= 32 && rM < 40 && !instores[rM] && 
		   rN < 256 && imm == 0)
	    {
	      /* mov rN, rM where rM is an input register */
	      reg_contents[rN] = rM;
	      last_prologue_pc = next_pc;
	    }
	  else if (frameless && qp == 0 && rN == fp_reg && imm == 0 && 
		   rM == 2)
	    {
	      /* mov r12, r2 */
	      last_prologue_pc = next_pc;
	      break;
	    }
	}
      else if (it == M 
            && (   ((instr & 0x1efc0000000LL) == 0x0eec0000000LL)
                || ((instr & 0x1ffc8000000LL) == 0x0cec0000000LL) ))
	{
	  /* stf.spill [rN] = fM, imm9
	     or
	     stf.spill [rN] = fM  */

	  int imm = imm9(instr);
	  int rN = (int) ((instr & 0x00007f00000LL) >> 20);
	  int fM = (int) ((instr & 0x000000fe000LL) >> 13);
	  int qp = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && rN == spill_reg && spill_addr != 0
	      && ((2 <= fM && fM <= 5) || (16 <= fM && fM <= 31)))
	    {
	      cache->saved_regs[IA64_FR0_REGNUM + fM] = spill_addr;

              if ((instr & 0x1efc0000000) == 0x0eec0000000)
		spill_addr += imm;
	      else
		spill_addr = 0;		/* last one; must be done */
	      last_prologue_pc = next_pc;
	    }
	}
      else if ((it == M && ((instr & 0x1eff8000000LL) == 0x02110000000LL))
            || (it == I && ((instr & 0x1eff8000000LL) == 0x00050000000LL)) )
	{
	  /* mov.m rN = arM   
	       or 
	     mov.i rN = arM */

	  int arM = (int) ((instr & 0x00007f00000LL) >> 20);
	  int rN  = (int) ((instr & 0x00000001fc0LL) >> 6);
	  int qp  = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && isScratch (rN) && arM == 36 /* ar.unat */)
	    {
	      /* We have something like "mov.m r3 = ar.unat".  Remember the
		 r3 (or whatever) and watch for a store of this register... */
	      unat_save_reg = rN;
	      last_prologue_pc = next_pc;
	    }
	}
      else if (it == I && ((instr & 0x1eff8000000LL) == 0x00198000000LL))
	{
	  /* mov rN = pr */
	  int rN  = (int) ((instr & 0x00000001fc0LL) >> 6);
	  int qp  = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && isScratch (rN))
	    {
	      pr_save_reg = rN;
	      last_prologue_pc = next_pc;
	    }
	}
      else if (it == M 
            && (   ((instr & 0x1ffc8000000LL) == 0x08cc0000000LL)
	        || ((instr & 0x1efc0000000LL) == 0x0acc0000000LL)))
	{
	  /* st8 [rN] = rM 
	      or
	     st8 [rN] = rM, imm9 */
	  int rN = (int) ((instr & 0x00007f00000LL) >> 20);
	  int rM = (int) ((instr & 0x000000fe000LL) >> 13);
	  int qp = (int) (instr & 0x0000000003fLL);
	  int indirect = rM < 256 ? reg_contents[rM] : 0;
	  if (qp == 0 && rN == spill_reg && spill_addr != 0
	      && (rM == unat_save_reg || rM == pr_save_reg))
	    {
	      /* We've found a spill of either the UNAT register or the PR
	         register.  (Well, not exactly; what we've actually found is
		 a spill of the register that UNAT or PR was moved to).
		 Record that fact and move on... */
	      if (rM == unat_save_reg)
		{
		  /* Track UNAT register */
		  cache->saved_regs[IA64_UNAT_REGNUM] = spill_addr;
		  unat_save_reg = 0;
		}
	      else
	        {
		  /* Track PR register */
		  cache->saved_regs[IA64_PR_REGNUM] = spill_addr;
		  pr_save_reg = 0;
		}
	      if ((instr & 0x1efc0000000LL) == 0x0acc0000000LL)
		/* st8 [rN] = rM, imm9 */
		spill_addr += imm9(instr);
	      else
		spill_addr = 0;		/* must be done spilling */
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && 32 <= rM && rM < 40 && !instores[rM-32])
	    {
	      /* Allow up to one store of each input register. */
	      instores[rM-32] = 1;
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && 32 <= indirect && indirect < 40 && 
		   !instores[indirect-32])
	    {
	      /* Allow an indirect store of an input register.  */
	      instores[indirect-32] = 1;
	      last_prologue_pc = next_pc;
	    }
	}
      else if (it == M && ((instr & 0x1ff08000000LL) == 0x08c00000000LL))
	{
	  /* One of
	       st1 [rN] = rM
	       st2 [rN] = rM
	       st4 [rN] = rM
	       st8 [rN] = rM
	     Note that the st8 case is handled in the clause above.
	     
	     Advance over stores of input registers. One store per input
	     register is permitted. */
	  int rM = (int) ((instr & 0x000000fe000LL) >> 13);
	  int qp = (int) (instr & 0x0000000003fLL);
	  int indirect = rM < 256 ? reg_contents[rM] : 0;
	  if (qp == 0 && 32 <= rM && rM < 40 && !instores[rM-32])
	    {
	      instores[rM-32] = 1;
	      last_prologue_pc = next_pc;
	    }
	  else if (qp == 0 && 32 <= indirect && indirect < 40 && 
		   !instores[indirect-32])
	    {
	      /* Allow an indirect store of an input register.  */
	      instores[indirect-32] = 1;
	      last_prologue_pc = next_pc;
	    }
	}
      else if (it == M && ((instr & 0x1ff88000000LL) == 0x0cc80000000LL))
        {
	  /* Either
	       stfs [rN] = fM
	     or
	       stfd [rN] = fM

	     Advance over stores of floating point input registers.  Again
	     one store per register is permitted */
	  int fM = (int) ((instr & 0x000000fe000LL) >> 13);
	  int qp = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && 8 <= fM && fM < 16 && !infpstores[fM - 8])
	    {
	      infpstores[fM-8] = 1;
	      last_prologue_pc = next_pc;
	    }
	}
      else if (it == M
            && (   ((instr & 0x1ffc8000000LL) == 0x08ec0000000LL)
	        || ((instr & 0x1efc0000000LL) == 0x0aec0000000LL)))
	{
	  /* st8.spill [rN] = rM
	       or
	     st8.spill [rN] = rM, imm9 */
	  int rN = (int) ((instr & 0x00007f00000LL) >> 20);
	  int rM = (int) ((instr & 0x000000fe000LL) >> 13);
	  int qp = (int) (instr & 0x0000000003fLL);
	  if (qp == 0 && rN == spill_reg && 4 <= rM && rM <= 7)
	    {
	      /* We've found a spill of one of the preserved general purpose
	         regs.  Record the spill address and advance the spill
		 register if appropriate. */
	      cache->saved_regs[IA64_GR0_REGNUM + rM] = spill_addr;
	      if ((instr & 0x1efc0000000LL) == 0x0aec0000000LL)
	        /* st8.spill [rN] = rM, imm9 */
		spill_addr += imm9(instr);
	      else
		spill_addr = 0;		/* Done spilling */
	      last_prologue_pc = next_pc;
	    }
	}

      pc = next_pc;
    }

  /* If not frameless and we aren't called by skip_prologue, then we need to calculate
     registers for the previous frame which will be needed later.  */

  if (!frameless && next_frame)
    {
      /* Extract the size of the rotating portion of the stack
	 frame and the register rename base from the current
	 frame marker. */
      cfm = cache->cfm;
      sor = cache->sor;
      sof = cache->sof;
      sol = cache->sol;
      rrb_gr = (cfm >> 18) & 0x7f;

      /* Find the bof (beginning of frame).  */
      bof = rse_address_add (cache->bsp, -sof);
      
      for (i = 0, addr = bof;
	   i < sof;
	   i++, addr += 8)
	{
	  if (IS_NaT_COLLECTION_ADDR (addr))
	    {
	      addr += 8;
	    }
	  if (i+32 == cfm_reg)
	    cache->saved_regs[IA64_CFM_REGNUM] = addr;
	  if (i+32 == ret_reg)
	    cache->saved_regs[IA64_VRAP_REGNUM] = addr;
	  if (i+32 == fp_reg)
	    cache->saved_regs[IA64_VFP_REGNUM] = addr;
	}

      /* For the previous argument registers we require the previous bof.  
	 If we can't find the previous cfm, then we can do nothing.  */
      cfm = 0;
      if (cache->saved_regs[IA64_CFM_REGNUM] != 0)
	{
	  uint64_t tmp;
	  ia64_read_reg (cache->saved_regs[IA64_CFM_REGNUM], &tmp, sizeof(tmp));
	  cfm = tmp;
	}
      else if (cfm_reg != 0)
	{
	  frame_unwind_register (next_frame, cfm_reg, buf);
	  cfm = extract_unsigned_integer (buf, 8);
	}
      cache->prev_cfm = cfm;
      
      if (cfm != 0)
	{
	  sor = ((cfm >> 14) & 0xf) * 8;
	  sof = (cfm & 0x7f);
	  sol = (cfm >> 7) & 0x7f;
	  rrb_gr = (cfm >> 18) & 0x7f;

	  /* The previous bof only requires subtraction of the sol (size of locals)
	     due to the overlap between output and input of subsequent frames.  */
	  bof = rse_address_add (bof, -sol);
	  
	  for (i = 0, addr = bof;
	       i < sof;
	       i++, addr += 8)
	    {
	      if (IS_NaT_COLLECTION_ADDR (addr))
		{
		  addr += 8;
		}
	      if (i < sor)
		cache->saved_regs[IA64_GR32_REGNUM + ((i + (sor - rrb_gr)) % sor)] 
		  = addr;
	      else
		cache->saved_regs[IA64_GR32_REGNUM + i] = addr;
	    }
	  
	}
    }
      
  /* Try and trust the lim_pc value whenever possible.  */
  if (trust_limit && lim_pc >= last_prologue_pc)
    last_prologue_pc = lim_pc;

  cache->frameless = frameless;
  cache->after_prologue = last_prologue_pc;
  cache->mem_stack_frame_size = mem_stack_frame_size;
  cache->fp_reg = fp_reg;

  return last_prologue_pc;
}