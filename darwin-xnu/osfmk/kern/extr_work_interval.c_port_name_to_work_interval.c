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
struct work_interval {int dummy; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PORT_NULL ; 
 int /*<<< orphan*/  IP_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_INVALID_CAPABILITY ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_space () ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_translate_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct work_interval* work_interval_port_convert_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
port_name_to_work_interval(mach_port_name_t     name,
                           struct work_interval **work_interval)
{
	if (!MACH_PORT_VALID(name))
		return KERN_INVALID_NAME;

	ipc_port_t port = IPC_PORT_NULL;
	kern_return_t kr = KERN_SUCCESS;

	kr = ipc_port_translate_send(current_space(), name, &port);
	if (kr != KERN_SUCCESS)
		return kr;
	/* port is locked */

	assert(IP_VALID(port));

	struct work_interval *converted_work_interval;

	converted_work_interval = work_interval_port_convert_locked(port);

	/* the port is valid, but doesn't denote a work_interval */
	if (converted_work_interval == NULL)
		kr = KERN_INVALID_CAPABILITY;

	ip_unlock(port);

	if (kr == KERN_SUCCESS)
		*work_interval = converted_work_interval;

	return kr;

}