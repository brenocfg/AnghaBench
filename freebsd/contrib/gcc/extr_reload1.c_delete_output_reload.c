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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ in; scalar_t__ in_reg; scalar_t__ out; scalar_t__ out_reg; scalar_t__ reg_rtx; } ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ INSN_DELETED_P (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 scalar_t__ NOTE_INSN_BASIC_BLOCK_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_BASIC_BLOCK (size_t) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 int REG_N_DEATHS (size_t) ; 
 int REG_N_SETS (size_t) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ USE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  alter_reg (size_t,int) ; 
 int count_occurrences (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_address_reloads (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 scalar_t__ eliminate_regs (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int** hard_regno_nregs ; 
 int n_reloads ; 
 scalar_t__* reg_equiv_alt_mem_list ; 
 scalar_t__* reg_equiv_memory_loc ; 
 scalar_t__ reg_mentioned_p (scalar_t__,scalar_t__) ; 
 size_t* reg_renumber ; 
 scalar_t__* reload_inherited ; 
 scalar_t__* reload_override_in ; 
 TYPE_1__* rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 scalar_t__* spill_reg_store ; 
 scalar_t__* spill_reg_stored_to ; 

__attribute__((used)) static void
delete_output_reload (rtx insn, int j, int last_reload_reg)
{
  rtx output_reload_insn = spill_reg_store[last_reload_reg];
  rtx reg = spill_reg_stored_to[last_reload_reg];
  int k;
  int n_occurrences;
  int n_inherited = 0;
  rtx i1;
  rtx substed;

  /* It is possible that this reload has been only used to set another reload
     we eliminated earlier and thus deleted this instruction too.  */
  if (INSN_DELETED_P (output_reload_insn))
    return;

  /* Get the raw pseudo-register referred to.  */

  while (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);
  substed = reg_equiv_memory_loc[REGNO (reg)];

  /* This is unsafe if the operand occurs more often in the current
     insn than it is inherited.  */
  for (k = n_reloads - 1; k >= 0; k--)
    {
      rtx reg2 = rld[k].in;
      if (! reg2)
	continue;
      if (MEM_P (reg2) || reload_override_in[k])
	reg2 = rld[k].in_reg;
#ifdef AUTO_INC_DEC
      if (rld[k].out && ! rld[k].out_reg)
	reg2 = XEXP (rld[k].in_reg, 0);
#endif
      while (GET_CODE (reg2) == SUBREG)
	reg2 = SUBREG_REG (reg2);
      if (rtx_equal_p (reg2, reg))
	{
	  if (reload_inherited[k] || reload_override_in[k] || k == j)
	    {
	      n_inherited++;
	      reg2 = rld[k].out_reg;
	      if (! reg2)
		continue;
	      while (GET_CODE (reg2) == SUBREG)
		reg2 = XEXP (reg2, 0);
	      if (rtx_equal_p (reg2, reg))
		n_inherited++;
	    }
	  else
	    return;
	}
    }
  n_occurrences = count_occurrences (PATTERN (insn), reg, 0);
  if (substed)
    n_occurrences += count_occurrences (PATTERN (insn),
					eliminate_regs (substed, 0,
							NULL_RTX), 0);
  for (i1 = reg_equiv_alt_mem_list [REGNO (reg)]; i1; i1 = XEXP (i1, 1))
    {
      gcc_assert (!rtx_equal_p (XEXP (i1, 0), substed));
      n_occurrences += count_occurrences (PATTERN (insn), XEXP (i1, 0), 0);
    }
  if (n_occurrences > n_inherited)
    return;

  /* If the pseudo-reg we are reloading is no longer referenced
     anywhere between the store into it and here,
     and we're within the same basic block, then the value can only
     pass through the reload reg and end up here.
     Otherwise, give up--return.  */
  for (i1 = NEXT_INSN (output_reload_insn);
       i1 != insn; i1 = NEXT_INSN (i1))
    {
      if (NOTE_INSN_BASIC_BLOCK_P (i1))
	return;
      if ((NONJUMP_INSN_P (i1) || CALL_P (i1))
	  && reg_mentioned_p (reg, PATTERN (i1)))
	{
	  /* If this is USE in front of INSN, we only have to check that
	     there are no more references than accounted for by inheritance.  */
	  while (NONJUMP_INSN_P (i1) && GET_CODE (PATTERN (i1)) == USE)
	    {
	      n_occurrences += rtx_equal_p (reg, XEXP (PATTERN (i1), 0)) != 0;
	      i1 = NEXT_INSN (i1);
	    }
	  if (n_occurrences <= n_inherited && i1 == insn)
	    break;
	  return;
	}
    }

  /* We will be deleting the insn.  Remove the spill reg information.  */
  for (k = hard_regno_nregs[last_reload_reg][GET_MODE (reg)]; k-- > 0; )
    {
      spill_reg_store[last_reload_reg + k] = 0;
      spill_reg_stored_to[last_reload_reg + k] = 0;
    }

  /* The caller has already checked that REG dies or is set in INSN.
     It has also checked that we are optimizing, and thus some
     inaccuracies in the debugging information are acceptable.
     So we could just delete output_reload_insn.  But in some cases
     we can improve the debugging information without sacrificing
     optimization - maybe even improving the code: See if the pseudo
     reg has been completely replaced with reload regs.  If so, delete
     the store insn and forget we had a stack slot for the pseudo.  */
  if (rld[j].out != rld[j].in
      && REG_N_DEATHS (REGNO (reg)) == 1
      && REG_N_SETS (REGNO (reg)) == 1
      && REG_BASIC_BLOCK (REGNO (reg)) >= 0
      && find_regno_note (insn, REG_DEAD, REGNO (reg)))
    {
      rtx i2;

      /* We know that it was used only between here and the beginning of
	 the current basic block.  (We also know that the last use before
	 INSN was the output reload we are thinking of deleting, but never
	 mind that.)  Search that range; see if any ref remains.  */
      for (i2 = PREV_INSN (insn); i2; i2 = PREV_INSN (i2))
	{
	  rtx set = single_set (i2);

	  /* Uses which just store in the pseudo don't count,
	     since if they are the only uses, they are dead.  */
	  if (set != 0 && SET_DEST (set) == reg)
	    continue;
	  if (LABEL_P (i2)
	      || JUMP_P (i2))
	    break;
	  if ((NONJUMP_INSN_P (i2) || CALL_P (i2))
	      && reg_mentioned_p (reg, PATTERN (i2)))
	    {
	      /* Some other ref remains; just delete the output reload we
		 know to be dead.  */
	      delete_address_reloads (output_reload_insn, insn);
	      delete_insn (output_reload_insn);
	      return;
	    }
	}

      /* Delete the now-dead stores into this pseudo.  Note that this
	 loop also takes care of deleting output_reload_insn.  */
      for (i2 = PREV_INSN (insn); i2; i2 = PREV_INSN (i2))
	{
	  rtx set = single_set (i2);

	  if (set != 0 && SET_DEST (set) == reg)
	    {
	      delete_address_reloads (i2, insn);
	      delete_insn (i2);
	    }
	  if (LABEL_P (i2)
	      || JUMP_P (i2))
	    break;
	}

      /* For the debugging info, say the pseudo lives in this reload reg.  */
      reg_renumber[REGNO (reg)] = REGNO (rld[j].reg_rtx);
      alter_reg (REGNO (reg), -1);
    }
  else
    {
      delete_address_reloads (output_reload_insn, insn);
      delete_insn (output_reload_insn);
    }
}