#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * r; } ;
struct TYPE_7__ {TYPE_1__ core; } ;
typedef  TYPE_2__ phase2_vrs ;
struct TYPE_8__ {TYPE_1__ core; int /*<<< orphan*/  demand_save_flags; } ;
typedef  TYPE_3__ phase1_vrs ;
typedef  scalar_t__ (* personality_routine ) (int,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  _uw ;
typedef  scalar_t__ (* _Unwind_Trace_Fn ) (int /*<<< orphan*/ *,void*) ;
typedef  scalar_t__ _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 size_t R_LR ; 
 size_t R_PC ; 
 scalar_t__ UCB_PR_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ _URC_END_OF_STACK ; 
 scalar_t__ _URC_FAILURE ; 
 scalar_t__ _URC_NO_REASON ; 
 scalar_t__ _URC_OK ; 
 int _US_FORCE_UNWIND ; 
 int _US_VIRTUAL_UNWIND_FRAME ; 
 int /*<<< orphan*/  _Unwind_SetGR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_eit_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_non_core_regs (TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ stub2 (int,int /*<<< orphan*/ *,void*) ; 

_Unwind_Reason_Code
__gnu_Unwind_Backtrace(_Unwind_Trace_Fn trace, void * trace_argument,
		       phase2_vrs * entry_vrs)
{
  phase1_vrs saved_vrs;
  _Unwind_Reason_Code code;

  _Unwind_Control_Block ucb;
  _Unwind_Control_Block *ucbp = &ucb;

  /* Set the pc to the call site.  */
  entry_vrs->core.r[R_PC] = entry_vrs->core.r[R_LR];

  /* Save the core registers.  */
  saved_vrs.core = entry_vrs->core;
  /* Set demand-save flags.  */
  saved_vrs.demand_save_flags = ~(_uw) 0;
  
  do
    {
      /* Find the entry for this routine.  */
      if ((code = get_eit_entry (ucbp, saved_vrs.core.r[R_PC])) != _URC_OK)
	  break;

      /* The dwarf unwinder assumes the context structure holds things
	 like the function and LSDA pointers.  The ARM implementation
	 caches these in the exception header (UCB).  To avoid
	 rewriting everything we make the virtual IP register point at
	 the UCB.  */
      _Unwind_SetGR((_Unwind_Context *)&saved_vrs, 12, (_Unwind_Ptr) ucbp);

      /* Call trace function.  */
      if ((*trace) ((_Unwind_Context *) &saved_vrs, trace_argument) 
	  != _URC_NO_REASON)
	{
	  code = _URC_FAILURE;
	  break;
	}

      /* Call the pr to decide what to do.  */
      code = ((personality_routine) UCB_PR_ADDR (ucbp))
	(_US_VIRTUAL_UNWIND_FRAME | _US_FORCE_UNWIND, 
	 ucbp, (void *) &saved_vrs);
    }
  while (code != _URC_END_OF_STACK
	 && code != _URC_FAILURE);

 finish:
  restore_non_core_regs (&saved_vrs);
  return code;
}