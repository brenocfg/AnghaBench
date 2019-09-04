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

/* Variables and functions */
 int /*<<< orphan*/  _kernelrpc_task_set_port_space (int /*<<< orphan*/ ,int) ; 

kern_return_t
task_set_port_space(
	ipc_space_t task,
	int table_entries)
{
	kern_return_t rv;

	rv = _kernelrpc_task_set_port_space(task, table_entries);

	return (rv);
}