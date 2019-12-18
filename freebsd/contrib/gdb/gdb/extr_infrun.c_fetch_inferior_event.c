#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cleanup {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  wait_some_more; int /*<<< orphan*/  wp; int /*<<< orphan*/  waiton_ptid; int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INF_EXEC_COMPLETE ; 
 int /*<<< orphan*/  INF_EXEC_CONTINUE ; 
 TYPE_1__* async_ecs ; 
 TYPE_1__ async_ecss ; 
 int /*<<< orphan*/  delete_breakpoint_current_contents ; 
 int /*<<< orphan*/  delete_step_resume_breakpoint ; 
 int /*<<< orphan*/  do_exec_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  handle_inferior_event (TYPE_1__*) ; 
 int /*<<< orphan*/  inferior_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_execution_control_state (TYPE_1__*) ; 
 struct cleanup* make_exec_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  normal_stop () ; 
 int overlay_cache_invalid ; 
 int /*<<< orphan*/  previous_inferior_ptid ; 
 int /*<<< orphan*/  registers_changed () ; 
 scalar_t__ step_multi ; 
 int /*<<< orphan*/  step_resume_breakpoint ; 
 scalar_t__ stop_step ; 
 int /*<<< orphan*/  target_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_wait_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  through_sigtramp_breakpoint ; 

void
fetch_inferior_event (void *client_data)
{
  static struct cleanup *old_cleanups;

  async_ecs = &async_ecss;

  if (!async_ecs->wait_some_more)
    {
      old_cleanups = make_exec_cleanup (delete_step_resume_breakpoint,
					&step_resume_breakpoint);
      make_exec_cleanup (delete_breakpoint_current_contents,
			 &through_sigtramp_breakpoint);

      /* Fill in with reasonable starting values.  */
      init_execution_control_state (async_ecs);

      /* We'll update this if & when we switch to a new thread. */
      previous_inferior_ptid = inferior_ptid;

      overlay_cache_invalid = 1;

      /* We have to invalidate the registers BEFORE calling target_wait
         because they can be loaded from the target while in target_wait.
         This makes remote debugging a bit more efficient for those
         targets that provide critical registers as part of their normal
         status mechanism. */

      registers_changed ();
    }

  if (target_wait_hook)
    async_ecs->ptid =
      target_wait_hook (async_ecs->waiton_ptid, async_ecs->wp);
  else
    async_ecs->ptid = target_wait (async_ecs->waiton_ptid, async_ecs->wp);

  /* Now figure out what to do with the result of the result.  */
  handle_inferior_event (async_ecs);

  if (!async_ecs->wait_some_more)
    {
      /* Do only the cleanups that have been added by this
         function. Let the continuations for the commands do the rest,
         if there are any. */
      do_exec_cleanups (old_cleanups);
      normal_stop ();
      if (step_multi && stop_step)
	inferior_event_handler (INF_EXEC_CONTINUE, NULL);
      else
	inferior_event_handler (INF_EXEC_COMPLETE, NULL);
    }
}