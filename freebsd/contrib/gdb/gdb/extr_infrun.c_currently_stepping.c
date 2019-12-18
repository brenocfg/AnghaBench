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
struct execution_control_state {scalar_t__ stepping_through_solib_after_catch; int /*<<< orphan*/  handling_longjmp; } ;

/* Variables and functions */
 scalar_t__ bpstat_should_step () ; 
 scalar_t__ step_range_end ; 
 int /*<<< orphan*/ * step_resume_breakpoint ; 
 int /*<<< orphan*/ * through_sigtramp_breakpoint ; 
 scalar_t__ trap_expected ; 

__attribute__((used)) static int
currently_stepping (struct execution_control_state *ecs)
{
  return ((through_sigtramp_breakpoint == NULL
	   && !ecs->handling_longjmp
	   && ((step_range_end && step_resume_breakpoint == NULL)
	       || trap_expected))
	  || ecs->stepping_through_solib_after_catch
	  || bpstat_should_step ());
}