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
 int /*<<< orphan*/  async_enable_stdin ; 
 int /*<<< orphan*/  make_exec_error_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_prompt (char*,char*,char*) ; 
 int sync_execution ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 

void
async_disable_stdin (void)
{
  sync_execution = 1;
  push_prompt ("", "", "");
  /* FIXME: cagney/1999-09-27: At present this call is technically
     redundant since infcmd.c and infrun.c both already call
     target_terminal_inferior().  As the terminal handling (in
     sync/async mode) is refined, the duplicate calls can be
     eliminated (Here or in infcmd.c/infrun.c). */
  target_terminal_inferior ();
  /* Add the reinstate of stdin to the list of cleanups to be done
     in case the target errors out and dies. These cleanups are also
     done in case of normal successful termination of the execution
     command, by complete_execution(). */
  make_exec_error_cleanup (async_enable_stdin, NULL);
}