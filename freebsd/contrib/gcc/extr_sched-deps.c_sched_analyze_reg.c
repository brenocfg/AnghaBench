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
struct deps {int max_reg; int /*<<< orphan*/  last_function_call; int /*<<< orphan*/  sched_before_next_call; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CLOBBER ; 
 int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DEP_ANTI ; 
 scalar_t__ REG_N_CALLS_CROSSED (int) ; 
 int SET ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
 int USE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dependence_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_INSN_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_reg_known_equiv_p (int) ; 
 int /*<<< orphan*/  get_reg_known_value (int) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  reg_pending_clobbers ; 
 int /*<<< orphan*/  reg_pending_sets ; 
 int /*<<< orphan*/  reg_pending_uses ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  sched_analyze_2 (struct deps*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sched_analyze_reg (struct deps *deps, int regno, enum machine_mode mode,
		   enum rtx_code ref, rtx insn)
{
  /* A hard reg in a wide mode may really be multiple registers.
     If so, mark all of them just like the first.  */
  if (regno < FIRST_PSEUDO_REGISTER)
    {
      int i = hard_regno_nregs[regno][mode];
      if (ref == SET)
	{
	  while (--i >= 0)
	    SET_REGNO_REG_SET (reg_pending_sets, regno + i);
	}
      else if (ref == USE)
	{
	  while (--i >= 0)
	    SET_REGNO_REG_SET (reg_pending_uses, regno + i);
	}
      else
	{
	  while (--i >= 0)
	    SET_REGNO_REG_SET (reg_pending_clobbers, regno + i);
	}
    }

  /* ??? Reload sometimes emits USEs and CLOBBERs of pseudos that
     it does not reload.  Ignore these as they have served their
     purpose already.  */
  else if (regno >= deps->max_reg)
    {
      enum rtx_code code = GET_CODE (PATTERN (insn));
      gcc_assert (code == USE || code == CLOBBER);
    }

  else
    {
      if (ref == SET)
	SET_REGNO_REG_SET (reg_pending_sets, regno);
      else if (ref == USE)
	SET_REGNO_REG_SET (reg_pending_uses, regno);
      else
	SET_REGNO_REG_SET (reg_pending_clobbers, regno);

      /* Pseudos that are REG_EQUIV to something may be replaced
	 by that during reloading.  We need only add dependencies for
	the address in the REG_EQUIV note.  */
      if (!reload_completed && get_reg_known_equiv_p (regno))
	{
	  rtx t = get_reg_known_value (regno);
	  if (MEM_P (t))
	    sched_analyze_2 (deps, XEXP (t, 0), insn);
	}

      /* Don't let it cross a call after scheduling if it doesn't
	 already cross one.  */
      if (REG_N_CALLS_CROSSED (regno) == 0)
	{
	  if (ref == USE)
	    deps->sched_before_next_call
	      = alloc_INSN_LIST (insn, deps->sched_before_next_call);
	  else
	    add_dependence_list (insn, deps->last_function_call, 1,
				 REG_DEP_ANTI);
	}
    }
}