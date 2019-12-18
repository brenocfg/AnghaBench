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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  proc_iterate_over_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_update_threads (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_notice_thread ; 

void
procfs_find_new_threads (void)
{
  procinfo *pi;

  /* Find procinfo for main process */
  pi = find_procinfo_or_die (PIDGET (inferior_ptid), 0);
  proc_update_threads (pi);
  proc_iterate_over_threads (pi, procfs_notice_thread, NULL);
}