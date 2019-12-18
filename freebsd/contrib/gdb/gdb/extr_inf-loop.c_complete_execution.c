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
 int /*<<< orphan*/  display_gdb_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_exec_error_cleanups (int /*<<< orphan*/ ) ; 
 scalar_t__ exec_done_display_p ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 scalar_t__ sync_execution ; 
 int /*<<< orphan*/  target_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ target_executing ; 

__attribute__((used)) static void
complete_execution (void)
{
  target_executing = 0;
  
  /* Unregister the inferior from the event loop. This is done so that
     when the inferior is not running we don't get distracted by
     spurious inferior output. */
  target_async (NULL, 0);

  if (sync_execution)
    {
      do_exec_error_cleanups (ALL_CLEANUPS);
      display_gdb_prompt (0);
    }
  else
    {
      if (exec_done_display_p)
	printf_unfiltered ("completed.\n");
    }
}