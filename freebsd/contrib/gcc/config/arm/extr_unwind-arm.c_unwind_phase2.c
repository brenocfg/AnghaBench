#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * r; } ;
struct TYPE_4__ {TYPE_3__ core; } ;
typedef  TYPE_1__ phase2_vrs ;
typedef  scalar_t__ (* personality_routine ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  scalar_t__ _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;
typedef  int /*<<< orphan*/  UCB_SAVED_CALLSITE_ADDR ;

/* Variables and functions */
 size_t R_PC ; 
 scalar_t__ UCB_PR_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ _URC_CONTINUE_UNWIND ; 
 scalar_t__ _URC_INSTALL_CONTEXT ; 
 scalar_t__ _URC_OK ; 
 int /*<<< orphan*/  _US_UNWIND_FRAME_STARTING ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ get_eit_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_core_regs (TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __attribute__((noreturn))
unwind_phase2 (_Unwind_Control_Block * ucbp, phase2_vrs * vrs)
{
  _Unwind_Reason_Code pr_result;

  do
    {
      /* Find the entry for this routine.  */
      if (get_eit_entry (ucbp, vrs->core.r[R_PC]) != _URC_OK)
	abort ();

      UCB_SAVED_CALLSITE_ADDR (ucbp) = vrs->core.r[R_PC];

      /* Call the pr to decide what to do.  */
      pr_result = ((personality_routine) UCB_PR_ADDR (ucbp))
	(_US_UNWIND_FRAME_STARTING, ucbp, (_Unwind_Context *) vrs);
    }
  while (pr_result == _URC_CONTINUE_UNWIND);
  
  if (pr_result != _URC_INSTALL_CONTEXT)
    abort();
  
  restore_core_regs (&vrs->core);
}