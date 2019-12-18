#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * r; } ;
struct TYPE_8__ {TYPE_1__ core; } ;
typedef  TYPE_2__ phase2_vrs ;
struct TYPE_9__ {TYPE_1__ core; int /*<<< orphan*/  demand_save_flags; } ;
typedef  TYPE_3__ phase1_vrs ;
typedef  scalar_t__ (* personality_routine ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  _uw ;
typedef  scalar_t__ _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;

/* Variables and functions */
 size_t R_LR ; 
 size_t R_PC ; 
 scalar_t__ UCB_PR_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ _URC_CONTINUE_UNWIND ; 
 scalar_t__ _URC_FAILURE ; 
 scalar_t__ _URC_HANDLER_FOUND ; 
 scalar_t__ _URC_OK ; 
 int /*<<< orphan*/  _US_VIRTUAL_UNWIND_FRAME ; 
 scalar_t__ get_eit_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_non_core_regs (TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  unwind_phase2 (int /*<<< orphan*/ *,TYPE_2__*) ; 

_Unwind_Reason_Code
__gnu_Unwind_RaiseException (_Unwind_Control_Block * ucbp,
			     phase2_vrs * entry_vrs)
{
  phase1_vrs saved_vrs;
  _Unwind_Reason_Code pr_result;

  /* Set the pc to the call site.  */
  entry_vrs->core.r[R_PC] = entry_vrs->core.r[R_LR];

  /* Save the core registers.  */
  saved_vrs.core = entry_vrs->core;
  /* Set demand-save flags.  */
  saved_vrs.demand_save_flags = ~(_uw) 0;
  
  /* Unwind until we reach a propagation barrier.  */
  do
    {
      /* Find the entry for this routine.  */
      if ((pr_result = get_eit_entry (ucbp, saved_vrs.core.r[R_PC])) != _URC_OK)
	return pr_result;

      /* Call the pr to decide what to do.  */
      pr_result = ((personality_routine) UCB_PR_ADDR (ucbp))
	(_US_VIRTUAL_UNWIND_FRAME, ucbp, (void *) &saved_vrs);
    }
  while (pr_result == _URC_CONTINUE_UNWIND);

  /* We've unwound as far as we want to go, so restore the original
     register state.  */
  restore_non_core_regs (&saved_vrs);
  if (pr_result != _URC_HANDLER_FOUND)
    {
      /* Some sort of failure has occurred in the pr and probably the
	 pr returned _URC_FAILURE.  */
      return _URC_FAILURE;
    }
  
  unwind_phase2 (ucbp, entry_vrs);
}