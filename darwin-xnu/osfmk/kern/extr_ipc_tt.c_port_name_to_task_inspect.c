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
typedef  int /*<<< orphan*/  task_inspect_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INSPECT_NULL ; 
 int /*<<< orphan*/  TASK_NULL ; 
 int /*<<< orphan*/  convert_port_to_task_inspect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_space () ; 
 scalar_t__ ipc_object_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 

task_inspect_t
port_name_to_task_inspect(
	mach_port_name_t name)
{
	ipc_port_t kern_port;
	kern_return_t kr;
	task_inspect_t ti = TASK_INSPECT_NULL;

	if (MACH_PORT_VALID(name)) {
		kr = ipc_object_copyin(current_space(), name,
		                       MACH_MSG_TYPE_COPY_SEND,
		                       (ipc_object_t *)&kern_port);
		if (kr != KERN_SUCCESS)
			return TASK_NULL;

		ti = convert_port_to_task_inspect(kern_port);

		if (IP_VALID(kern_port))
			ipc_port_release_send(kern_port);
	}
	return ti;
}