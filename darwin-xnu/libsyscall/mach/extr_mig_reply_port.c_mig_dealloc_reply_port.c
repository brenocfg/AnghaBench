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
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 scalar_t__ _mig_get_reply_port () ; 
 int /*<<< orphan*/  _mig_set_reply_port (scalar_t__) ; 
 scalar_t__ _task_reply_port ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mach_port_mod_refs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 

void
mig_dealloc_reply_port(mach_port_t migport)
{
	mach_port_t port = _mig_get_reply_port();
	if (port != MACH_PORT_NULL && port != _task_reply_port) {
		_mig_set_reply_port(_task_reply_port);
		(void) mach_port_mod_refs(mach_task_self(), port, MACH_PORT_RIGHT_RECEIVE, -1);
		if (migport != port) {
			(void) mach_port_deallocate(mach_task_self(), migport);
		}
		_mig_set_reply_port(MACH_PORT_NULL);
	}
}