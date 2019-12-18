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
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  target_stop () ; 

__attribute__((used)) static void
async_remote_interrupt (gdb_client_data arg)
{
  if (remote_debug)
    fprintf_unfiltered (gdb_stdlog, "remote_interrupt called\n");

  target_stop ();
}