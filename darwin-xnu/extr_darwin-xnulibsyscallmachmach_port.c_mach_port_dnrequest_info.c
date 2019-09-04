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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kernelrpc_mach_port_dnrequest_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

kern_return_t
mach_port_dnrequest_info(
	ipc_space_t task,
	mach_port_name_t name,
	unsigned *dnr_total,
	unsigned *dnr_used)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_port_dnrequest_info(task, name, dnr_total,
			dnr_used);

	return (rv);
}