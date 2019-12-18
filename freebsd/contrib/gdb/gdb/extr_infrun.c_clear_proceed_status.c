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
 int /*<<< orphan*/  NO_STOP_QUIETLY ; 
 int /*<<< orphan*/  STEP_OVER_UNDEBUGGABLE ; 
 int /*<<< orphan*/  bpstat_clear (int /*<<< orphan*/ *) ; 
 int breakpoint_proceeded ; 
 int /*<<< orphan*/  null_frame_id ; 
 scalar_t__ proceed_to_finish ; 
 int /*<<< orphan*/  step_frame_id ; 
 int /*<<< orphan*/  step_over_calls ; 
 scalar_t__ step_range_end ; 
 scalar_t__ step_range_start ; 
 scalar_t__ stop_after_trap ; 
 int /*<<< orphan*/  stop_bpstat ; 
 int /*<<< orphan*/  stop_soon ; 
 scalar_t__ trap_expected ; 

void
clear_proceed_status (void)
{
  trap_expected = 0;
  step_range_start = 0;
  step_range_end = 0;
  step_frame_id = null_frame_id;
  step_over_calls = STEP_OVER_UNDEBUGGABLE;
  stop_after_trap = 0;
  stop_soon = NO_STOP_QUIETLY;
  proceed_to_finish = 0;
  breakpoint_proceeded = 1;	/* We're about to proceed... */

  /* Discard any remaining commands or status from previous stop.  */
  bpstat_clear (&stop_bpstat);
}