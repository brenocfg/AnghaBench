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
typedef  int /*<<< orphan*/  ttevents_t ;

/* Variables and functions */
 scalar_t__ CHILD_URPED (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CHILD_VFORKED (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PARENT_VFORKED (int /*<<< orphan*/ ,int) ; 
 int vfork_in_flight ; 
 int vforking_child_pid ; 

__attribute__((used)) static int
can_touch_threads_of_process (int pid, ttevents_t stopping_event)
{
  if (CHILD_VFORKED (stopping_event, pid))
    {
      vforking_child_pid = pid;
      vfork_in_flight = 1;
    }

  else if (vfork_in_flight &&
	   (PARENT_VFORKED (stopping_event, pid) ||
	    CHILD_URPED (stopping_event, pid)))
    {
      vfork_in_flight = 0;
      vforking_child_pid = 0;
    }

  return !vfork_in_flight;
}