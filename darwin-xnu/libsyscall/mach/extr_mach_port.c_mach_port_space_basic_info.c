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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_info_space_basic_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kernelrpc_mach_port_space_basic_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_space_basic_info(
	ipc_space_t task,
	ipc_info_space_basic_t *space_basic_info)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_port_space_basic_info(task, space_basic_info);

	return (rv);
}