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
 int /*<<< orphan*/ * find_procinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/  unconditionally_kill_inferior (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfs_kill_inferior (void)
{
  if (!ptid_equal (inferior_ptid, null_ptid)) /* ? */
    {
      /* Find procinfo for main process */
      procinfo *pi = find_procinfo (PIDGET (inferior_ptid), 0);

      if (pi)
	unconditionally_kill_inferior (pi);
      target_mourn_inferior ();
    }
}