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
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  handle_remote_sigint ; 
 int /*<<< orphan*/  interrupt_query () ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_executing ; 

void
async_remote_interrupt_twice (gdb_client_data arg)
{
  if (remote_debug)
    fprintf_unfiltered (gdb_stdlog, "remote_interrupt_twice called\n");
  /* Do something only if the target was not killed by the previous
     cntl-C. */
  if (target_executing)
    {
      interrupt_query ();
      signal (SIGINT, handle_remote_sigint);
    }
}