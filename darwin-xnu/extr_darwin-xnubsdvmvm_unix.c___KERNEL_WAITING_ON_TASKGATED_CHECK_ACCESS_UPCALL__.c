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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int check_task_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((noinline)) int __KERNEL_WAITING_ON_TASKGATED_CHECK_ACCESS_UPCALL__(
	mach_port_t task_access_port, int32_t calling_pid, uint32_t calling_gid, int32_t target_pid)
{
	return check_task_access(task_access_port, calling_pid, calling_gid, target_pid);
}