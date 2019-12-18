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
typedef  TYPE_1__* work_interval_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {int create_flags; int /*<<< orphan*/  wi_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_SEND ; 
 int WORK_INTERVAL_FLAG_JOINABLE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ mach_port_mod_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 

int
work_interval_copy_port(work_interval_t interval_handle, mach_port_t *port)
{
	if (port == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (interval_handle == NULL) {
		*port = MACH_PORT_NULL;
		errno = EINVAL;
		return -1;
	}

	if ((interval_handle->create_flags & WORK_INTERVAL_FLAG_JOINABLE) == 0) {
		*port = MACH_PORT_NULL;
		errno = EINVAL;
		return -1;
	}

	mach_port_t wi_port = interval_handle->wi_port;

	kern_return_t kr = mach_port_mod_refs(mach_task_self(), wi_port,
	                                      MACH_PORT_RIGHT_SEND, 1);

	if (kr != KERN_SUCCESS) {
		*port = MACH_PORT_NULL;
		errno = EINVAL;
		return -1;
	}

	*port = wi_port;

	return 0;
}