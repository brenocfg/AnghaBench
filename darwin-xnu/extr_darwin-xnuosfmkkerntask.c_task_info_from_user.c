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
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  task_info_t ;
typedef  int /*<<< orphan*/  task_flavor_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_DYLD_INFO ; 
 int /*<<< orphan*/  convert_port_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_port_to_task_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
task_info_from_user(
	mach_port_t		task_port,
	task_flavor_t		flavor,
	task_info_t		task_info_out,
	mach_msg_type_number_t	*task_info_count)
{
	task_t task;
	kern_return_t ret;

	if (flavor == TASK_DYLD_INFO)
		task = convert_port_to_task(task_port);
	else
		task = convert_port_to_task_name(task_port);

	ret = task_info(task, flavor, task_info_out, task_info_count);

	task_deallocate(task);

	return ret;
}