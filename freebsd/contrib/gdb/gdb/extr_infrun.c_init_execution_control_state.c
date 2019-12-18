#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  symtab; int /*<<< orphan*/  line; } ;
struct execution_control_state {int /*<<< orphan*/  ws; int /*<<< orphan*/ * wp; int /*<<< orphan*/  waiton_ptid; int /*<<< orphan*/  infwait_state; TYPE_1__ sal; int /*<<< orphan*/  current_symtab; int /*<<< orphan*/  current_line; scalar_t__ stepping_through_sigtramp; scalar_t__ enable_hw_watchpoints_after_wait; int /*<<< orphan*/ * stepping_through_solib_catchpoints; scalar_t__ stepping_through_solib_after_catch; scalar_t__ update_step_sp; scalar_t__ handling_longjmp; scalar_t__ remove_breakpoints_on_following_step; scalar_t__ random_signal; } ;

/* Variables and functions */
 TYPE_1__ find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infwait_normal_state ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  prev_pc ; 

void
init_execution_control_state (struct execution_control_state *ecs)
{
  /* ecs->another_trap? */
  ecs->random_signal = 0;
  ecs->remove_breakpoints_on_following_step = 0;
  ecs->handling_longjmp = 0;	/* FIXME */
  ecs->update_step_sp = 0;
  ecs->stepping_through_solib_after_catch = 0;
  ecs->stepping_through_solib_catchpoints = NULL;
  ecs->enable_hw_watchpoints_after_wait = 0;
  ecs->stepping_through_sigtramp = 0;
  ecs->sal = find_pc_line (prev_pc, 0);
  ecs->current_line = ecs->sal.line;
  ecs->current_symtab = ecs->sal.symtab;
  ecs->infwait_state = infwait_normal_state;
  ecs->waiton_ptid = pid_to_ptid (-1);
  ecs->wp = &(ecs->ws);
}