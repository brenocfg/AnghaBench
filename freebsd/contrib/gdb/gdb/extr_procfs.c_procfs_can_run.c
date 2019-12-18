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
 int /*<<< orphan*/  procfs_suppress_run ; 

__attribute__((used)) static int
procfs_can_run (void)
{
  /* This variable is controlled by modules that sit atop procfs that
     may layer their own process structure atop that provided here.
     sol-thread.c does this because of the Solaris two-level thread
     model.  */

  /* NOTE: possibly obsolete -- use the thread_stratum approach instead. */

  return !procfs_suppress_run;
}