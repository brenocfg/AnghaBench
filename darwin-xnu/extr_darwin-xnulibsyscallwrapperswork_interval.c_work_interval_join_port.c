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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ mach_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  WORK_INTERVAL_OPERATION_JOIN ; 
 int __work_interval_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
work_interval_join_port(mach_port_t port)
{
	if (port == MACH_PORT_NULL) {
		errno = EINVAL;
		return -1;
	}

	return __work_interval_ctl(WORK_INTERVAL_OPERATION_JOIN,
	                           (uint64_t)port, NULL, 0);
}