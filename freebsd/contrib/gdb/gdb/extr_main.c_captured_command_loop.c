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
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int /*<<< orphan*/  current_interp_command_loop () ; 
 int /*<<< orphan*/  do_cleanups (int /*<<< orphan*/ ) ; 
 scalar_t__ instream ; 
 int /*<<< orphan*/  quit_command (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stdin ; 

__attribute__((used)) static int
captured_command_loop (void *data)
{
  current_interp_command_loop ();
  /* FIXME: cagney/1999-11-05: A correct command_loop() implementaton
     would clean things up (restoring the cleanup chain) to the state
     they were just prior to the call.  Technically, this means that
     the do_cleanups() below is redundant.  Unfortunately, many FUNCs
     are not that well behaved.  do_cleanups should either be replaced
     with a do_cleanups call (to cover the problem) or an assertion
     check to detect bad FUNCs code. */
  do_cleanups (ALL_CLEANUPS);
  /* If the command_loop returned, normally (rather than threw an
     error) we try to quit. If the quit is aborted, catch_errors()
     which called this catch the signal and restart the command
     loop. */
  quit_command (NULL, instream == stdin);
  return 1;
}