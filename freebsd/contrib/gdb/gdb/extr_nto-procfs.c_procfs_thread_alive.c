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
typedef  int /*<<< orphan*/  tid ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_CURTHREAD ; 
 scalar_t__ EOK ; 
 int /*<<< orphan*/  ctl_fd ; 
 scalar_t__ devctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_get_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
procfs_thread_alive (ptid_t ptid)
{
  pid_t tid;

  tid = ptid_get_tid (ptid);
  if (devctl (ctl_fd, DCMD_PROC_CURTHREAD, &tid, sizeof (tid), 0) == EOK)
    return 1;
  return 0;
}