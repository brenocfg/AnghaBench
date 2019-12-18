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
typedef  int /*<<< orphan*/  vm_purgeable_info_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  task_purgable_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  task_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  task_reference (scalar_t__) ; 
 int /*<<< orphan*/  vm_purgeable_stats (int /*<<< orphan*/ ,scalar_t__) ; 

kern_return_t
task_purgable_info(
	task_t			task,
	task_purgable_info_t	*stats)
{
	if (task == TASK_NULL || stats == NULL)
		return KERN_INVALID_ARGUMENT;
	/* Take task reference */
	task_reference(task);
	vm_purgeable_stats((vm_purgeable_info_t)stats, task);
	/* Drop task reference */
	task_deallocate(task);
	return KERN_SUCCESS;
}