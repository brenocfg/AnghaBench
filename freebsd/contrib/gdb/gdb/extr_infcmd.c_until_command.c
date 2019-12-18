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
 int /*<<< orphan*/  async_disable_stdin () ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ event_loop_p ; 
 int strip_bg_char (char**) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  target_has_execution ; 
 int /*<<< orphan*/  until_break_command (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  until_next_command (int) ; 

__attribute__((used)) static void
until_command (char *arg, int from_tty)
{
  int async_exec = 0;

  if (!target_has_execution)
    error ("The program is not running.");

  /* Find out whether we must run in the background. */
  if (arg != NULL)
    async_exec = strip_bg_char (&arg);

  /* If we must run in the background, but the target can't do it,
     error out. */
  if (event_loop_p && async_exec && !target_can_async_p ())
    error ("Asynchronous execution not supported on this target.");

  /* If we are not asked to run in the bg, then prepare to run in the
     foreground, synchronously. */
  if (event_loop_p && !async_exec && target_can_async_p ())
    {
      /* Simulate synchronous execution */
      async_disable_stdin ();
    }

  if (arg)
    until_break_command (arg, from_tty, 0);
  else
    until_next_command (from_tty);
}