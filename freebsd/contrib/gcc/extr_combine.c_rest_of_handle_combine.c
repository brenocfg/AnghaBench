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
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_UPDATE_LIFE ; 
 int /*<<< orphan*/  TV_JUMP ; 
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 int combine_instructions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_dead_jumptables () ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  rebuild_jump_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_combine (void)
{
  int rebuild_jump_labels_after_combine
    = combine_instructions (get_insns (), max_reg_num ());

  /* Combining insns may have turned an indirect jump into a
     direct jump.  Rebuild the JUMP_LABEL fields of jumping
     instructions.  */
  if (rebuild_jump_labels_after_combine)
    {
      timevar_push (TV_JUMP);
      rebuild_jump_labels (get_insns ());
      timevar_pop (TV_JUMP);

      delete_dead_jumptables ();
      cleanup_cfg (CLEANUP_EXPENSIVE | CLEANUP_UPDATE_LIFE);
    }
  return 0;
}