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
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  local_hex_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  vx_running ; 

__attribute__((used)) static void
vx_run_files_info (void)
{
  printf_unfiltered ("\tRunning %s VxWorks process %s",
		     vx_running ? "child" : "attached",
		     local_hex_string (PIDGET (inferior_ptid)));
  if (vx_running)
    printf_unfiltered (", function `%s'", vx_running);
  printf_unfiltered (".\n");
}