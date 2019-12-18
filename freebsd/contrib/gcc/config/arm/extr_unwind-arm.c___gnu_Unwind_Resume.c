#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * r; } ;
struct TYPE_6__ {TYPE_4__ core; } ;
typedef  TYPE_1__ phase2_vrs ;
typedef  int (* personality_routine ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 size_t R_PC ; 
 scalar_t__ UCB_FORCED_STOP_FN (int /*<<< orphan*/ *) ; 
 scalar_t__ UCB_PR_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UCB_SAVED_CALLSITE_ADDR (int /*<<< orphan*/ *) ; 
#define  _URC_CONTINUE_UNWIND 129 
#define  _URC_INSTALL_CONTEXT 128 
 int /*<<< orphan*/  _US_UNWIND_FRAME_RESUME ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  restore_core_regs (TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unwind_phase2 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  unwind_phase2_forced (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

_Unwind_Reason_Code
__gnu_Unwind_Resume (_Unwind_Control_Block * ucbp, phase2_vrs * entry_vrs)
{
  _Unwind_Reason_Code pr_result;

  /* Recover the saved address.  */
  entry_vrs->core.r[R_PC] = UCB_SAVED_CALLSITE_ADDR (ucbp);

  if (UCB_FORCED_STOP_FN (ucbp))
    {
      unwind_phase2_forced (ucbp, entry_vrs, 1);

      /* We can't return failure at this point.  */
      abort ();
    }

  /* Call the cached PR.  */
  pr_result = ((personality_routine) UCB_PR_ADDR (ucbp))
	(_US_UNWIND_FRAME_RESUME, ucbp, (_Unwind_Context *) entry_vrs);

  switch (pr_result)
    {
    case _URC_INSTALL_CONTEXT:
      /* Upload the registers to enter the landing pad.  */
      restore_core_regs (&entry_vrs->core);

    case _URC_CONTINUE_UNWIND:
      /* Continue unwinding the next frame.  */
      unwind_phase2 (ucbp, entry_vrs);

    default:
      abort ();
    }
}