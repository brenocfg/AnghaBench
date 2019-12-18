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
struct execution_control_state {scalar_t__ infwait_state; int wait_some_more; int /*<<< orphan*/  ws; int /*<<< orphan*/ * wp; int /*<<< orphan*/  waiton_ptid; } ;

/* Variables and functions */
 scalar_t__ infwait_normal_state ; 
 int overlay_cache_invalid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  registers_changed () ; 

__attribute__((used)) static void
prepare_to_wait (struct execution_control_state *ecs)
{
  if (ecs->infwait_state == infwait_normal_state)
    {
      overlay_cache_invalid = 1;

      /* We have to invalidate the registers BEFORE calling
         target_wait because they can be loaded from the target while
         in target_wait.  This makes remote debugging a bit more
         efficient for those targets that provide critical registers
         as part of their normal status mechanism. */

      registers_changed ();
      ecs->waiton_ptid = pid_to_ptid (-1);
      ecs->wp = &(ecs->ws);
    }
  /* This is the old end of the while loop.  Let everybody know we
     want to wait for the inferior some more and get called again
     soon.  */
  ecs->wait_some_more = 1;
}