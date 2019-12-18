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
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  extended_remote_restart () ; 
 int /*<<< orphan*/  inferior_event_handler ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  proceed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_breakpoints () ; 
 int /*<<< orphan*/  target_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_can_async_p () ; 

__attribute__((used)) static void
extended_remote_async_create_inferior (char *exec_file, char *args, char **env)
{
  /* Rip out the breakpoints; we'll reinsert them after restarting
     the remote server.  */
  remove_breakpoints ();

  /* If running asynchronously, register the target file descriptor
     with the event loop. */
  if (event_loop_p && target_can_async_p ())
    target_async (inferior_event_handler, 0);

  /* Now restart the remote server.  */
  extended_remote_restart ();

  /* Now put the breakpoints back in.  This way we're safe if the
     restart function works via a unix fork on the remote side.  */
  insert_breakpoints ();

  /* Clean up from the last time we were running.  */
  clear_proceed_status ();

  /* Let the remote process run.  */
  proceed (-1, TARGET_SIGNAL_0, 0);
}