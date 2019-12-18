#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sjlj_lp_info {int call_site_index; } ;
struct eh_region {size_t region_number; } ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  sjlj_fc; int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_EH_REGION ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  emit_insn_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ find_first_parameter_load (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_non_call_exceptions ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ may_trap_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sjlj_fc_call_site_ofs ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static void
sjlj_mark_call_sites (struct sjlj_lp_info *lp_info)
{
  int last_call_site = -2;
  rtx insn, mem;

  for (insn = get_insns (); insn ; insn = NEXT_INSN (insn))
    {
      struct eh_region *region;
      int this_call_site;
      rtx note, before, p;

      /* Reset value tracking at extended basic block boundaries.  */
      if (LABEL_P (insn))
	last_call_site = -2;

      if (! INSN_P (insn))
	continue;

      note = find_reg_note (insn, REG_EH_REGION, NULL_RTX);
      if (!note)
	{
	  /* Calls (and trapping insns) without notes are outside any
	     exception handling region in this function.  Mark them as
	     no action.  */
	  if (CALL_P (insn)
	      || (flag_non_call_exceptions
		  && may_trap_p (PATTERN (insn))))
	    this_call_site = -1;
	  else
	    continue;
	}
      else
	{
	  /* Calls that are known to not throw need not be marked.  */
	  if (INTVAL (XEXP (note, 0)) <= 0)
	    continue;

	  region = VEC_index (eh_region, cfun->eh->region_array, INTVAL (XEXP (note, 0)));
	  this_call_site = lp_info[region->region_number].call_site_index;
	}

      if (this_call_site == last_call_site)
	continue;

      /* Don't separate a call from it's argument loads.  */
      before = insn;
      if (CALL_P (insn))
	before = find_first_parameter_load (insn, NULL_RTX);

      start_sequence ();
      mem = adjust_address (cfun->eh->sjlj_fc, TYPE_MODE (integer_type_node),
			    sjlj_fc_call_site_ofs);
      emit_move_insn (mem, GEN_INT (this_call_site));
      p = get_insns ();
      end_sequence ();

      emit_insn_before (p, before);
      last_call_site = this_call_site;
    }
}