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
struct bundle_state {int insn; int before_nops_num; int after_nops_num; int accumulated_insns_num; int branch_deviation; int /*<<< orphan*/  dfa_state; struct bundle_state* allocated_states_chain; int /*<<< orphan*/  cost; struct bundle_state* originator; scalar_t__ insn_num; } ;
typedef  int /*<<< orphan*/  state_t ;
typedef  int rtx ;

/* Variables and functions */
 scalar_t__ ASM_INPUT ; 
 scalar_t__ CODE_FOR_insn_group_barrier ; 
 scalar_t__ FIRST_INSN_YES ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int) ; 
 scalar_t__ INSN_CODE (int) ; 
 int /*<<< orphan*/  PATTERN (int) ; 
 scalar_t__ TImode ; 
 scalar_t__ TYPE_B ; 
 scalar_t__ TYPE_L ; 
 scalar_t__ asm_noperands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dfa_pre_cycle_insn ; 
 int /*<<< orphan*/  dfa_state_size ; 
 int /*<<< orphan*/  free_bundle_state (struct bundle_state*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_attr_first_insn (int) ; 
 struct bundle_state* get_free_bundle_state () ; 
 scalar_t__ ia64_safe_type (int) ; 
 scalar_t__ insert_bundle_state (struct bundle_state*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_dfa_state ; 
 int /*<<< orphan*/  try_issue_insn (struct bundle_state*,int) ; 
 int /*<<< orphan*/  try_issue_nops (struct bundle_state*,int) ; 

__attribute__((used)) static void
issue_nops_and_insn (struct bundle_state *originator, int before_nops_num,
		     rtx insn, int try_bundle_end_p, int only_bundle_end_p)
{
  struct bundle_state *curr_state;

  curr_state = get_free_bundle_state ();
  memcpy (curr_state->dfa_state, originator->dfa_state, dfa_state_size);
  curr_state->insn = insn;
  curr_state->insn_num = originator->insn_num + 1;
  curr_state->cost = originator->cost;
  curr_state->originator = originator;
  curr_state->before_nops_num = before_nops_num;
  curr_state->after_nops_num = 0;
  curr_state->accumulated_insns_num
    = originator->accumulated_insns_num + before_nops_num;
  curr_state->branch_deviation = originator->branch_deviation;
  gcc_assert (insn);
  if (INSN_CODE (insn) == CODE_FOR_insn_group_barrier)
    {
      gcc_assert (GET_MODE (insn) != TImode);
      if (!try_issue_nops (curr_state, before_nops_num))
	return;
      if (!try_issue_insn (curr_state, insn))
	return;
      memcpy (temp_dfa_state, curr_state->dfa_state, dfa_state_size);
      if (state_transition (temp_dfa_state, dfa_pre_cycle_insn) >= 0
	  && curr_state->accumulated_insns_num % 3 != 0)
	{
	  free_bundle_state (curr_state);
	  return;
	}
    }
  else if (GET_MODE (insn) != TImode)
    {
      if (!try_issue_nops (curr_state, before_nops_num))
	return;
      if (!try_issue_insn (curr_state, insn))
	return;
      curr_state->accumulated_insns_num++;
      gcc_assert (GET_CODE (PATTERN (insn)) != ASM_INPUT
		  && asm_noperands (PATTERN (insn)) < 0);

      if (ia64_safe_type (insn) == TYPE_L)
	curr_state->accumulated_insns_num++;
    }
  else
    {
      /* If this is an insn that must be first in a group, then don't allow
	 nops to be emitted before it.  Currently, alloc is the only such
	 supported instruction.  */
      /* ??? The bundling automatons should handle this for us, but they do
	 not yet have support for the first_insn attribute.  */
      if (before_nops_num > 0 && get_attr_first_insn (insn) == FIRST_INSN_YES)
	{
	  free_bundle_state (curr_state);
	  return;
	}

      state_transition (curr_state->dfa_state, dfa_pre_cycle_insn);
      state_transition (curr_state->dfa_state, NULL);
      curr_state->cost++;
      if (!try_issue_nops (curr_state, before_nops_num))
	return;
      if (!try_issue_insn (curr_state, insn))
	return;
      curr_state->accumulated_insns_num++;
      if (GET_CODE (PATTERN (insn)) == ASM_INPUT
	  || asm_noperands (PATTERN (insn)) >= 0)
	{
	  /* Finish bundle containing asm insn.  */
	  curr_state->after_nops_num
	    = 3 - curr_state->accumulated_insns_num % 3;
	  curr_state->accumulated_insns_num
	    += 3 - curr_state->accumulated_insns_num % 3;
	}
      else if (ia64_safe_type (insn) == TYPE_L)
	curr_state->accumulated_insns_num++;
    }
  if (ia64_safe_type (insn) == TYPE_B)
    curr_state->branch_deviation
      += 2 - (curr_state->accumulated_insns_num - 1) % 3;
  if (try_bundle_end_p && curr_state->accumulated_insns_num % 3 != 0)
    {
      if (!only_bundle_end_p && insert_bundle_state (curr_state))
	{
	  state_t dfa_state;
	  struct bundle_state *curr_state1;
	  struct bundle_state *allocated_states_chain;

	  curr_state1 = get_free_bundle_state ();
	  dfa_state = curr_state1->dfa_state;
	  allocated_states_chain = curr_state1->allocated_states_chain;
	  *curr_state1 = *curr_state;
	  curr_state1->dfa_state = dfa_state;
	  curr_state1->allocated_states_chain = allocated_states_chain;
	  memcpy (curr_state1->dfa_state, curr_state->dfa_state,
		  dfa_state_size);
	  curr_state = curr_state1;
	}
      if (!try_issue_nops (curr_state,
			   3 - curr_state->accumulated_insns_num % 3))
	return;
      curr_state->after_nops_num
	= 3 - curr_state->accumulated_insns_num % 3;
      curr_state->accumulated_insns_num
	+= 3 - curr_state->accumulated_insns_num % 3;
    }
  if (!insert_bundle_state (curr_state))
    free_bundle_state (curr_state);
  return;
}