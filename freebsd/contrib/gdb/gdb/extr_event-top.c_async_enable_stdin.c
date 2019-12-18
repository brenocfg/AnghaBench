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
 int /*<<< orphan*/  pop_prompt () ; 
 scalar_t__ sync_execution ; 
 int /*<<< orphan*/  target_terminal_ours () ; 

void
async_enable_stdin (void *dummy)
{
  /* See NOTE in async_disable_stdin() */
  /* FIXME: cagney/1999-09-27: Call this before clearing
     sync_execution.  Current target_terminal_ours() implementations
     check for sync_execution before switching the terminal. */
  target_terminal_ours ();
  pop_prompt ();
  sync_execution = 0;
}