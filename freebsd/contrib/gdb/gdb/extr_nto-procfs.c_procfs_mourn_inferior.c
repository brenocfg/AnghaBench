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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SignalKill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_fd ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_thread_list () ; 
 int /*<<< orphan*/  nto_node () ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfs_mourn_inferior (void)
{
  if (!ptid_equal (inferior_ptid, null_ptid))
    {
      SignalKill (nto_node(), PIDGET (inferior_ptid), 0, SIGKILL, 0, 0);
      close (ctl_fd);
    }
  inferior_ptid = null_ptid;
  init_thread_list ();
  unpush_target (&procfs_ops);
  generic_mourn_inferior ();
  attach_flag = 0;
}