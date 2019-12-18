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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
struct TYPE_3__ {int (* issue_rate ) () ;} ;
struct TYPE_4__ {int (* branch_target_register_class ) () ;int /*<<< orphan*/  (* branch_target_register_callee_saved ) (int) ;TYPE_1__ sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CLEANUP_EXPENSIVE ; 
 int NO_REGS ; 
 int PROP_DEATH_NOTES ; 
 int PROP_REG_INFO ; 
 int /*<<< orphan*/  UPDATE_LIFE_GLOBAL_RM_NOTES ; 
 int /*<<< orphan*/  calculate_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int issue_rate ; 
 int /*<<< orphan*/  life_analysis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migrate_btr_defs (int,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 int stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (int) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  update_life_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
branch_target_load_optimize (bool after_prologue_epilogue_gen)
{
  enum reg_class class = targetm.branch_target_register_class ();
  if (class != NO_REGS)
    {
      /* Initialize issue_rate.  */
      if (targetm.sched.issue_rate)
	issue_rate = targetm.sched.issue_rate ();
      else
	issue_rate = 1;

      /* Build the CFG for migrate_btr_defs.  */
#if 1
      /* This may or may not be needed, depending on where we
	 run this phase.  */
      cleanup_cfg (optimize ? CLEANUP_EXPENSIVE : 0);
#endif

      life_analysis (0);

      /* Dominator info is also needed for migrate_btr_def.  */
      calculate_dominance_info (CDI_DOMINATORS);
      migrate_btr_defs (class,
		       (targetm.branch_target_register_callee_saved
			(after_prologue_epilogue_gen)));

      free_dominance_info (CDI_DOMINATORS);

      update_life_info (NULL, UPDATE_LIFE_GLOBAL_RM_NOTES,
			PROP_DEATH_NOTES | PROP_REG_INFO);
    }
}