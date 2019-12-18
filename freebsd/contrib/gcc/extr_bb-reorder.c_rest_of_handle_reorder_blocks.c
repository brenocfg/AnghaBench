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

/* Variables and functions */
 unsigned int CLEANUP_EXPENSIVE ; 
 unsigned int CLEANUP_UPDATE_LIFE ; 
 scalar_t__ HAVE_conditional_execution ; 
 int /*<<< orphan*/  PROP_DEATH_NOTES ; 
 int /*<<< orphan*/  TV_TRACER ; 
 int /*<<< orphan*/  UPDATE_LIFE_GLOBAL_RM_NOTES ; 
 int cleanup_cfg (unsigned int) ; 
 scalar_t__ flag_reorder_blocks ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 
 scalar_t__ flag_sched2_use_traces ; 
 scalar_t__ flag_schedule_insns_after_reload ; 
 int /*<<< orphan*/  insert_section_boundary_note () ; 
 int /*<<< orphan*/  reorder_basic_blocks (unsigned int) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracer (unsigned int) ; 
 int /*<<< orphan*/  update_life_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_reorder_blocks (void)
{
  bool changed;
  unsigned int liveness_flags;

  /* Last attempt to optimize CFG, as scheduling, peepholing and insn
     splitting possibly introduced more crossjumping opportunities.  */
  liveness_flags = (!HAVE_conditional_execution ? CLEANUP_UPDATE_LIFE : 0);
  changed = cleanup_cfg (CLEANUP_EXPENSIVE | liveness_flags);

  if (flag_sched2_use_traces && flag_schedule_insns_after_reload)
    {
      timevar_push (TV_TRACER);
      tracer (liveness_flags);
      timevar_pop (TV_TRACER);
    }

  if (flag_reorder_blocks || flag_reorder_blocks_and_partition)
    reorder_basic_blocks (liveness_flags);
  if (flag_reorder_blocks || flag_reorder_blocks_and_partition
      || (flag_sched2_use_traces && flag_schedule_insns_after_reload))
    changed |= cleanup_cfg (CLEANUP_EXPENSIVE | liveness_flags);

  /* On conditional execution targets we can not update the life cheaply, so
     we deffer the updating to after both cleanups.  This may lose some cases
     but should not be terribly bad.  */
  if (changed && HAVE_conditional_execution)
    update_life_info (NULL, UPDATE_LIFE_GLOBAL_RM_NOTES,
		      PROP_DEATH_NOTES);

  /* Add NOTE_INSN_SWITCH_TEXT_SECTIONS notes.  */
  insert_section_boundary_note ();
  return 0;
}