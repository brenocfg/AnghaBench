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
 int /*<<< orphan*/  STOP_QUIETLY ; 
 int /*<<< orphan*/  init_thread_list () ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  normal_stop () ; 
 int /*<<< orphan*/  stop_soon ; 
 scalar_t__ trap_expected ; 
 int /*<<< orphan*/  wait_for_inferior () ; 

void
start_remote (void)
{
  init_thread_list ();
  init_wait_for_inferior ();
  stop_soon = STOP_QUIETLY;
  trap_expected = 0;

  /* Always go on waiting for the target, regardless of the mode. */
  /* FIXME: cagney/1999-09-23: At present it isn't possible to
     indicate to wait_for_inferior that a target should timeout if
     nothing is returned (instead of just blocking).  Because of this,
     targets expecting an immediate response need to, internally, set
     things up so that the target_wait() is forced to eventually
     timeout. */
  /* FIXME: cagney/1999-09-24: It isn't possible for target_open() to
     differentiate to its caller what the state of the target is after
     the initial open has been performed.  Here we're assuming that
     the target has stopped.  It should be possible to eventually have
     target_open() return to the caller an indication that the target
     is currently running and GDB state should be set to the same as
     for an async run. */
  wait_for_inferior ();
  normal_stop ();
}