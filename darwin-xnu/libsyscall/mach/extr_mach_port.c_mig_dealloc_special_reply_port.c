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
typedef  scalar_t__ mach_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 scalar_t__ MACH_PORT_VALID (scalar_t__) ; 
 int /*<<< orphan*/  THREAD_SPECIAL_REPLY_PORT_ALL ; 
 scalar_t__ _tsd_get_special_reply_port () ; 
 int /*<<< orphan*/  _tsd_set_special_reply_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  thread_destruct_special_reply_port (scalar_t__,int /*<<< orphan*/ ) ; 

void
mig_dealloc_special_reply_port(mach_port_t migport)
{
	mach_port_t srp = _tsd_get_special_reply_port();
	if (MACH_PORT_VALID(srp)) {
		thread_destruct_special_reply_port(srp, THREAD_SPECIAL_REPLY_PORT_ALL);
		if (migport != srp) {
			mach_port_deallocate(mach_task_self(), migport);
		}
		_tsd_set_special_reply_port(MACH_PORT_NULL);
	}
}