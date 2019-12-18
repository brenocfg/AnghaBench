#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_3__ {int tid; } ;
typedef  TYPE_1__ procfs_status ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_TIDSTATUS ; 
 scalar_t__ EOK ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int ctl_fd ; 
 scalar_t__ devctl (int,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  ptid_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptid_get_pid (int /*<<< orphan*/ ) ; 

void
procfs_find_new_threads (void)
{
  procfs_status status;
  pid_t pid;
  ptid_t ptid;

  if (ctl_fd == -1)
    return;

  pid = ptid_get_pid (inferior_ptid);

  for (status.tid = 1;; ++status.tid)
    {
      if (devctl (ctl_fd, DCMD_PROC_TIDSTATUS, &status, sizeof (status), 0)
	  != EOK && status.tid != 0)
	break;
      ptid = ptid_build (pid, 0, status.tid);
      if (!in_thread_list (ptid))
	add_thread (ptid);
    }
  return;
}