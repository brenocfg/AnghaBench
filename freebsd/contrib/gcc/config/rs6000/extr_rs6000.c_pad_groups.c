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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ TImode ; 
 int /*<<< orphan*/  current_group ; 
 int /*<<< orphan*/  emit_insn_before (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_nop () ; 
 scalar_t__ get_next_active_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  insn_terminates_group_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_branch_slot_insn (scalar_t__) ; 
 int /*<<< orphan*/  previous_group ; 
 int rs6000_issue_rate () ; 
 scalar_t__ rs6000_sched_insert_nops ; 
 int rs6000_variable_issue (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 scalar_t__ sched_finish_pad_groups ; 

__attribute__((used)) static int
pad_groups (FILE *dump, int sched_verbose, rtx prev_head_insn, rtx tail)
{
  rtx insn, next_insn;
  rtx nop;
  int issue_rate;
  int can_issue_more;
  int group_end;
  int group_count = 0;

  /* Initialize issue_rate.  */
  issue_rate = rs6000_issue_rate ();
  can_issue_more = issue_rate;

  insn = get_next_active_insn (prev_head_insn, tail);
  next_insn = get_next_active_insn (insn, tail);

  while (insn != NULL_RTX)
    {
      can_issue_more =
      	rs6000_variable_issue (dump, sched_verbose, insn, can_issue_more);

      group_end = (next_insn == NULL_RTX || GET_MODE (next_insn) == TImode);

      if (next_insn == NULL_RTX)
	break;

      if (group_end)
	{
	  /* If the scheduler had marked group termination at this location
	     (between insn and next_indn), and neither insn nor next_insn will
	     force group termination, pad the group with nops to force group
	     termination.  */
	  if (can_issue_more
	      && (rs6000_sched_insert_nops == sched_finish_pad_groups)
	      && !insn_terminates_group_p (insn, current_group)
	      && !insn_terminates_group_p (next_insn, previous_group))
	    {
	      if (!is_branch_slot_insn (next_insn))
		can_issue_more--;

	      while (can_issue_more)
		{
		  nop = gen_nop ();
		  emit_insn_before (nop, next_insn);
		  can_issue_more--;
		}
	    }

	  can_issue_more = issue_rate;
	  group_count++;
	}

      insn = next_insn;
      next_insn = get_next_active_insn (insn, tail);
    }

  return group_count;
}