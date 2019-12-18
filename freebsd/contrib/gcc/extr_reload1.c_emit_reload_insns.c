#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct insn_chain {void* insn; } ;
typedef  void* rtx ;
struct TYPE_4__ {void* reg_rtx; scalar_t__ in_reg; scalar_t__ out; void* out_reg; scalar_t__ in; size_t mode; int /*<<< orphan*/  when_needed; int /*<<< orphan*/  opnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (void*) ; 
 size_t GET_MODE (void*) ; 
 scalar_t__ HARD_REGNO_CALL_PART_CLOBBERED (int,size_t) ; 
 int INSN_UID (void*) ; 
 int /*<<< orphan*/  IOR_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (void*) ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (void*) ; 
 int REGNO (void*) ; 
 int /*<<< orphan*/  REGNO_REG_SET_P (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 scalar_t__ REG_P (void*) ; 
 scalar_t__ SET_DEST (void*) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ *,int) ; 
 void* SET_SRC (void*) ; 
 scalar_t__ SUBREG ; 
 void* SUBREG_REG (void*) ; 
 void* XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_reload_to_stream (scalar_t__) ; 
 int /*<<< orphan*/  do_input_reload (struct insn_chain*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  do_output_reload (struct insn_chain*,TYPE_1__*,int) ; 
 scalar_t__ dump_file ; 
 void* emit_insn_after (scalar_t__,void*) ; 
 int /*<<< orphan*/  emit_insn_before (scalar_t__,void*) ; 
 void* find_regno_note (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 
 int** hard_regno_nregs ; 
 scalar_t__ inherit_piecemeal_p (int,int) ; 
 scalar_t__* inpaddr_address_reload_insns ; 
 scalar_t__* input_address_reload_insns ; 
 scalar_t__* input_reload_insns ; 
 int n_reloads ; 
 void** new_spill_reg_store ; 
 scalar_t__ operand_reload_insns ; 
 scalar_t__ other_input_address_reload_insns ; 
 scalar_t__ other_input_reload_insns ; 
 scalar_t__ other_operand_reload_insns ; 
 scalar_t__* other_output_reload_insns ; 
 scalar_t__* outaddr_address_reload_insns ; 
 scalar_t__* output_address_reload_insns ; 
 scalar_t__* output_reload_insns ; 
 int /*<<< orphan*/  reg_has_output_reload ; 
 int /*<<< orphan*/  reg_is_output_reload ; 
 void** reg_last_reload_reg ; 
 int /*<<< orphan*/  reg_reloaded_call_part_clobbered ; 
 int* reg_reloaded_contents ; 
 int /*<<< orphan*/  reg_reloaded_dead ; 
 int /*<<< orphan*/  reg_reloaded_died ; 
 void** reg_reloaded_insn ; 
 int /*<<< orphan*/  reg_reloaded_valid ; 
 int /*<<< orphan*/  reg_set_p (void*,int /*<<< orphan*/ ) ; 
 void** regno_reg_rtx ; 
 scalar_t__* reload_inherited ; 
 int reload_n_operands ; 
 int* reload_order ; 
 scalar_t__* reload_override_in ; 
 scalar_t__ reload_reg_reaches_end_p (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* reload_spill_index ; 
 TYPE_1__* rld ; 
 void* single_set (void*) ; 
 void** spill_reg_store ; 
 void** spill_reg_stored_to ; 

__attribute__((used)) static void
emit_reload_insns (struct insn_chain *chain)
{
  rtx insn = chain->insn;

  int j;

  CLEAR_HARD_REG_SET (reg_reloaded_died);

  for (j = 0; j < reload_n_operands; j++)
    input_reload_insns[j] = input_address_reload_insns[j]
      = inpaddr_address_reload_insns[j]
      = output_reload_insns[j] = output_address_reload_insns[j]
      = outaddr_address_reload_insns[j]
      = other_output_reload_insns[j] = 0;
  other_input_address_reload_insns = 0;
  other_input_reload_insns = 0;
  operand_reload_insns = 0;
  other_operand_reload_insns = 0;

  /* Dump reloads into the dump file.  */
  if (dump_file)
    {
      fprintf (dump_file, "\nReloads for insn # %d\n", INSN_UID (insn));
      debug_reload_to_stream (dump_file);
    }

  /* Now output the instructions to copy the data into and out of the
     reload registers.  Do these in the order that the reloads were reported,
     since reloads of base and index registers precede reloads of operands
     and the operands may need the base and index registers reloaded.  */

  for (j = 0; j < n_reloads; j++)
    {
      if (rld[j].reg_rtx
	  && REGNO (rld[j].reg_rtx) < FIRST_PSEUDO_REGISTER)
	new_spill_reg_store[REGNO (rld[j].reg_rtx)] = 0;

      do_input_reload (chain, rld + j, j);
      do_output_reload (chain, rld + j, j);
    }

  /* Now write all the insns we made for reloads in the order expected by
     the allocation functions.  Prior to the insn being reloaded, we write
     the following reloads:

     RELOAD_FOR_OTHER_ADDRESS reloads for input addresses.

     RELOAD_OTHER reloads.

     For each operand, any RELOAD_FOR_INPADDR_ADDRESS reloads followed
     by any RELOAD_FOR_INPUT_ADDRESS reloads followed by the
     RELOAD_FOR_INPUT reload for the operand.

     RELOAD_FOR_OPADDR_ADDRS reloads.

     RELOAD_FOR_OPERAND_ADDRESS reloads.

     After the insn being reloaded, we write the following:

     For each operand, any RELOAD_FOR_OUTADDR_ADDRESS reloads followed
     by any RELOAD_FOR_OUTPUT_ADDRESS reload followed by the
     RELOAD_FOR_OUTPUT reload, followed by any RELOAD_OTHER output
     reloads for the operand.  The RELOAD_OTHER output reloads are
     output in descending order by reload number.  */

  emit_insn_before (other_input_address_reload_insns, insn);
  emit_insn_before (other_input_reload_insns, insn);

  for (j = 0; j < reload_n_operands; j++)
    {
      emit_insn_before (inpaddr_address_reload_insns[j], insn);
      emit_insn_before (input_address_reload_insns[j], insn);
      emit_insn_before (input_reload_insns[j], insn);
    }

  emit_insn_before (other_operand_reload_insns, insn);
  emit_insn_before (operand_reload_insns, insn);

  for (j = 0; j < reload_n_operands; j++)
    {
      rtx x = emit_insn_after (outaddr_address_reload_insns[j], insn);
      x = emit_insn_after (output_address_reload_insns[j], x);
      x = emit_insn_after (output_reload_insns[j], x);
      emit_insn_after (other_output_reload_insns[j], x);
    }

  /* For all the spill regs newly reloaded in this instruction,
     record what they were reloaded from, so subsequent instructions
     can inherit the reloads.

     Update spill_reg_store for the reloads of this insn.
     Copy the elements that were updated in the loop above.  */

  for (j = 0; j < n_reloads; j++)
    {
      int r = reload_order[j];
      int i = reload_spill_index[r];

      /* If this is a non-inherited input reload from a pseudo, we must
	 clear any memory of a previous store to the same pseudo.  Only do
	 something if there will not be an output reload for the pseudo
	 being reloaded.  */
      if (rld[r].in_reg != 0
	  && ! (reload_inherited[r] || reload_override_in[r]))
	{
	  rtx reg = rld[r].in_reg;

	  if (GET_CODE (reg) == SUBREG)
	    reg = SUBREG_REG (reg);

	  if (REG_P (reg)
	      && REGNO (reg) >= FIRST_PSEUDO_REGISTER
	      && !REGNO_REG_SET_P (&reg_has_output_reload, REGNO (reg)))
	    {
	      int nregno = REGNO (reg);

	      if (reg_last_reload_reg[nregno])
		{
		  int last_regno = REGNO (reg_last_reload_reg[nregno]);

		  if (reg_reloaded_contents[last_regno] == nregno)
		    spill_reg_store[last_regno] = 0;
		}
	    }
	}

      /* I is nonneg if this reload used a register.
	 If rld[r].reg_rtx is 0, this is an optional reload
	 that we opted to ignore.  */

      if (i >= 0 && rld[r].reg_rtx != 0)
	{
	  int nr = hard_regno_nregs[i][GET_MODE (rld[r].reg_rtx)];
	  int k;
	  int part_reaches_end = 0;
	  int all_reaches_end = 1;

	  /* For a multi register reload, we need to check if all or part
	     of the value lives to the end.  */
	  for (k = 0; k < nr; k++)
	    {
	      if (reload_reg_reaches_end_p (i + k, rld[r].opnum,
					    rld[r].when_needed))
		part_reaches_end = 1;
	      else
		all_reaches_end = 0;
	    }

	  /* Ignore reloads that don't reach the end of the insn in
	     entirety.  */
	  if (all_reaches_end)
	    {
	      /* First, clear out memory of what used to be in this spill reg.
		 If consecutive registers are used, clear them all.  */

	      for (k = 0; k < nr; k++)
  	        {
		CLEAR_HARD_REG_BIT (reg_reloaded_valid, i + k);
  		  CLEAR_HARD_REG_BIT (reg_reloaded_call_part_clobbered, i + k);
  		}

	      /* Maybe the spill reg contains a copy of reload_out.  */
	      if (rld[r].out != 0
		  && (REG_P (rld[r].out)
#ifdef AUTO_INC_DEC
		      || ! rld[r].out_reg
#endif
		      || REG_P (rld[r].out_reg)))
		{
		  rtx out = (REG_P (rld[r].out)
			     ? rld[r].out
			     : rld[r].out_reg
			     ? rld[r].out_reg
/* AUTO_INC */		     : XEXP (rld[r].in_reg, 0));
		  int nregno = REGNO (out);
		  int nnr = (nregno >= FIRST_PSEUDO_REGISTER ? 1
			     : hard_regno_nregs[nregno]
					       [GET_MODE (rld[r].reg_rtx)]);
		  bool piecemeal;

		  spill_reg_store[i] = new_spill_reg_store[i];
		  spill_reg_stored_to[i] = out;
		  reg_last_reload_reg[nregno] = rld[r].reg_rtx;

		  piecemeal = (nregno < FIRST_PSEUDO_REGISTER
			       && nr == nnr
			       && inherit_piecemeal_p (r, nregno));

		  /* If NREGNO is a hard register, it may occupy more than
		     one register.  If it does, say what is in the
		     rest of the registers assuming that both registers
		     agree on how many words the object takes.  If not,
		     invalidate the subsequent registers.  */

		  if (nregno < FIRST_PSEUDO_REGISTER)
		    for (k = 1; k < nnr; k++)
		      reg_last_reload_reg[nregno + k]
			= (piecemeal
			   ? regno_reg_rtx[REGNO (rld[r].reg_rtx) + k]
			   : 0);

		  /* Now do the inverse operation.  */
		  for (k = 0; k < nr; k++)
		    {
		      CLEAR_HARD_REG_BIT (reg_reloaded_dead, i + k);
		      reg_reloaded_contents[i + k]
			= (nregno >= FIRST_PSEUDO_REGISTER || !piecemeal
			   ? nregno
			   : nregno + k);
		      reg_reloaded_insn[i + k] = insn;
		      SET_HARD_REG_BIT (reg_reloaded_valid, i + k);
		      if (HARD_REGNO_CALL_PART_CLOBBERED (i + k, GET_MODE (out)))
			SET_HARD_REG_BIT (reg_reloaded_call_part_clobbered, i + k);
		    }
		}

	      /* Maybe the spill reg contains a copy of reload_in.  Only do
		 something if there will not be an output reload for
		 the register being reloaded.  */
	      else if (rld[r].out_reg == 0
		       && rld[r].in != 0
		       && ((REG_P (rld[r].in)
			    && REGNO (rld[r].in) >= FIRST_PSEUDO_REGISTER
	                    && !REGNO_REG_SET_P (&reg_has_output_reload,
			      			 REGNO (rld[r].in)))
			   || (REG_P (rld[r].in_reg)
			       && !REGNO_REG_SET_P (&reg_has_output_reload,
						    REGNO (rld[r].in_reg))))
		       && ! reg_set_p (rld[r].reg_rtx, PATTERN (insn)))
		{
		  int nregno;
		  int nnr;
		  rtx in;
		  bool piecemeal;

		  if (REG_P (rld[r].in)
		      && REGNO (rld[r].in) >= FIRST_PSEUDO_REGISTER)
		    in = rld[r].in;
		  else if (REG_P (rld[r].in_reg))
		    in = rld[r].in_reg;
		  else
		    in = XEXP (rld[r].in_reg, 0);
		  nregno = REGNO (in);

		  nnr = (nregno >= FIRST_PSEUDO_REGISTER ? 1
			 : hard_regno_nregs[nregno]
					   [GET_MODE (rld[r].reg_rtx)]);

		  reg_last_reload_reg[nregno] = rld[r].reg_rtx;

		  piecemeal = (nregno < FIRST_PSEUDO_REGISTER
			       && nr == nnr
			       && inherit_piecemeal_p (r, nregno));

		  if (nregno < FIRST_PSEUDO_REGISTER)
		    for (k = 1; k < nnr; k++)
		      reg_last_reload_reg[nregno + k]
			= (piecemeal
			   ? regno_reg_rtx[REGNO (rld[r].reg_rtx) + k]
			   : 0);

		  /* Unless we inherited this reload, show we haven't
		     recently done a store.
		     Previous stores of inherited auto_inc expressions
		     also have to be discarded.  */
		  if (! reload_inherited[r]
		      || (rld[r].out && ! rld[r].out_reg))
		    spill_reg_store[i] = 0;

		  for (k = 0; k < nr; k++)
		    {
		      CLEAR_HARD_REG_BIT (reg_reloaded_dead, i + k);
		      reg_reloaded_contents[i + k]
			= (nregno >= FIRST_PSEUDO_REGISTER || !piecemeal
			   ? nregno
			   : nregno + k);
		      reg_reloaded_insn[i + k] = insn;
		      SET_HARD_REG_BIT (reg_reloaded_valid, i + k);
		      if (HARD_REGNO_CALL_PART_CLOBBERED (i + k, GET_MODE (in)))
			SET_HARD_REG_BIT (reg_reloaded_call_part_clobbered, i + k);
		    }
		}
	    }

	  /* However, if part of the reload reaches the end, then we must
	     invalidate the old info for the part that survives to the end.  */
	  else if (part_reaches_end)
	    {
	      for (k = 0; k < nr; k++)
		if (reload_reg_reaches_end_p (i + k,
					      rld[r].opnum,
					      rld[r].when_needed))
		  CLEAR_HARD_REG_BIT (reg_reloaded_valid, i + k);
	    }
	}

      /* The following if-statement was #if 0'd in 1.34 (or before...).
	 It's reenabled in 1.35 because supposedly nothing else
	 deals with this problem.  */

      /* If a register gets output-reloaded from a non-spill register,
	 that invalidates any previous reloaded copy of it.
	 But forget_old_reloads_1 won't get to see it, because
	 it thinks only about the original insn.  So invalidate it here.
	 Also do the same thing for RELOAD_OTHER constraints where the
	 output is discarded.  */
      if (i < 0 
	  && ((rld[r].out != 0
	       && (REG_P (rld[r].out)
		   || (MEM_P (rld[r].out)
		       && REG_P (rld[r].out_reg))))
	      || (rld[r].out == 0 && rld[r].out_reg
		  && REG_P (rld[r].out_reg))))
	{
	  rtx out = ((rld[r].out && REG_P (rld[r].out))
		     ? rld[r].out : rld[r].out_reg);
	  int nregno = REGNO (out);
	  if (nregno >= FIRST_PSEUDO_REGISTER)
	    {
	      rtx src_reg, store_insn = NULL_RTX;

	      reg_last_reload_reg[nregno] = 0;

	      /* If we can find a hard register that is stored, record
		 the storing insn so that we may delete this insn with
		 delete_output_reload.  */
	      src_reg = rld[r].reg_rtx;

	      /* If this is an optional reload, try to find the source reg
		 from an input reload.  */
	      if (! src_reg)
		{
		  rtx set = single_set (insn);
		  if (set && SET_DEST (set) == rld[r].out)
		    {
		      int k;

		      src_reg = SET_SRC (set);
		      store_insn = insn;
		      for (k = 0; k < n_reloads; k++)
			{
			  if (rld[k].in == src_reg)
			    {
			      src_reg = rld[k].reg_rtx;
			      break;
			    }
			}
		    }
		}
	      else
		store_insn = new_spill_reg_store[REGNO (src_reg)];
	      if (src_reg && REG_P (src_reg)
		  && REGNO (src_reg) < FIRST_PSEUDO_REGISTER)
		{
		  int src_regno = REGNO (src_reg);
		  int nr = hard_regno_nregs[src_regno][rld[r].mode];
		  /* The place where to find a death note varies with
		     PRESERVE_DEATH_INFO_REGNO_P .  The condition is not
		     necessarily checked exactly in the code that moves
		     notes, so just check both locations.  */
		  rtx note = find_regno_note (insn, REG_DEAD, src_regno);
		  if (! note && store_insn)
		    note = find_regno_note (store_insn, REG_DEAD, src_regno);
		  while (nr-- > 0)
		    {
		      spill_reg_store[src_regno + nr] = store_insn;
		      spill_reg_stored_to[src_regno + nr] = out;
		      reg_reloaded_contents[src_regno + nr] = nregno;
		      reg_reloaded_insn[src_regno + nr] = store_insn;
		      CLEAR_HARD_REG_BIT (reg_reloaded_dead, src_regno + nr);
		      SET_HARD_REG_BIT (reg_reloaded_valid, src_regno + nr);
		      if (HARD_REGNO_CALL_PART_CLOBBERED (src_regno + nr, 
							  GET_MODE (src_reg)))
			SET_HARD_REG_BIT (reg_reloaded_call_part_clobbered, 
					  src_regno + nr);
		      SET_HARD_REG_BIT (reg_is_output_reload, src_regno + nr);
		      if (note)
			SET_HARD_REG_BIT (reg_reloaded_died, src_regno);
		      else
			CLEAR_HARD_REG_BIT (reg_reloaded_died, src_regno);
		    }
		  reg_last_reload_reg[nregno] = src_reg;
		  /* We have to set reg_has_output_reload here, or else 
		     forget_old_reloads_1 will clear reg_last_reload_reg
		     right away.  */
		  SET_REGNO_REG_SET (&reg_has_output_reload,
				     nregno);
		}
	    }
	  else
	    {
	      int num_regs = hard_regno_nregs[nregno][GET_MODE (out)];

	      while (num_regs-- > 0)
		reg_last_reload_reg[nregno + num_regs] = 0;
	    }
	}
    }
  IOR_HARD_REG_SET (reg_reloaded_dead, reg_reloaded_died);
}