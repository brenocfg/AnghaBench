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
struct TYPE_3__ {int type; int size; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ procfs_break ;
typedef  int /*<<< orphan*/  brk ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_BREAK ; 
 scalar_t__ EOK ; 
 int /*<<< orphan*/  ctl_fd ; 
 scalar_t__ devctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 

__attribute__((used)) static int
procfs_breakpoint (CORE_ADDR addr, int type, int size)
{
  procfs_break brk;

  brk.type = type;
  brk.addr = addr;
  brk.size = size;
  errno = devctl (ctl_fd, DCMD_PROC_BREAK, &brk, sizeof (brk), 0);
  if (errno != EOK)
    return 1;
  return 0;
}