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
typedef  int /*<<< orphan*/  vm_map_copy_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ dyld_kernel_image_info_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DYLD_UUID_UNMAP_A ; 
 int /*<<< orphan*/  kdebug_trace_dyld (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
task_unregister_dyld_image_infos(task_t task,
                                 dyld_kernel_image_info_array_t infos_copy,
                                 mach_msg_type_number_t infos_len)
{
	return kdebug_trace_dyld(task, DBG_DYLD_UUID_UNMAP_A,
		(vm_map_copy_t)infos_copy, infos_len);
}