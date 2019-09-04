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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_port_name_array_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kernelrpc_mach_port_get_set_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_get_set_status(
	ipc_space_t task,
	mach_port_name_t name,
	mach_port_name_array_t *members,
	mach_msg_type_number_t *membersCnt)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_port_get_set_status(task, name, members,
			membersCnt);

	return (rv);
}