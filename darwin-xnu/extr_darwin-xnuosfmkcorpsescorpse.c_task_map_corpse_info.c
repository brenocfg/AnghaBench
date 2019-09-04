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
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ task_map_corpse_info_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

kern_return_t
task_map_corpse_info(
	task_t task,
	task_t corpse_task,
	vm_address_t *kcd_addr_begin,
	uint32_t *kcd_size)
{
	kern_return_t kr;
	mach_vm_address_t kcd_addr_begin_64;
	mach_vm_size_t size_64;

	kr = task_map_corpse_info_64(task, corpse_task, &kcd_addr_begin_64, &size_64);
	if (kr != KERN_SUCCESS) {
		return kr;
	}

	*kcd_addr_begin = (vm_address_t)kcd_addr_begin_64;
	*kcd_size = (uint32_t) size_64;
	return KERN_SUCCESS;
}