#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {void* wait_for_space; void* no_zero_fill; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MSG_OOL_SIZE_SMALL_MAX ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 scalar_t__ cpy_kdata_hdr_sz ; 
 int /*<<< orphan*/  ipc_host_init () ; 
 TYPE_1__* ipc_kernel_copy_map ; 
 int /*<<< orphan*/  ipc_kernel_copy_map_size ; 
 TYPE_1__* ipc_kernel_map ; 
 int /*<<< orphan*/  ipc_kernel_map_size ; 
 scalar_t__ kalloc_max_prerounded ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_suballoc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ msg_ool_size_small ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  ux_handler_init () ; 

void
ipc_init(void)
{
	kern_return_t retval;
	vm_offset_t min;

	retval = kmem_suballoc(kernel_map, &min, ipc_kernel_map_size,
			       TRUE,
			       (VM_FLAGS_ANYWHERE),
			       VM_MAP_KERNEL_FLAGS_NONE,
			       VM_KERN_MEMORY_IPC,
			       &ipc_kernel_map);

	if (retval != KERN_SUCCESS)
		panic("ipc_init: kmem_suballoc of ipc_kernel_map failed");

	retval = kmem_suballoc(kernel_map, &min, ipc_kernel_copy_map_size,
			       TRUE,
			       (VM_FLAGS_ANYWHERE),
			       VM_MAP_KERNEL_FLAGS_NONE,
			       VM_KERN_MEMORY_IPC,
			       &ipc_kernel_copy_map);

	if (retval != KERN_SUCCESS)
		panic("ipc_init: kmem_suballoc of ipc_kernel_copy_map failed");

	ipc_kernel_copy_map->no_zero_fill = TRUE;
	ipc_kernel_copy_map->wait_for_space = TRUE;

	/*
	 * As an optimization, 'small' out of line data regions using a 
	 * physical copy strategy are copied into kalloc'ed buffers.
	 * The value of 'small' is determined here.  Requests kalloc()
	 * with sizes greater or equal to kalloc_max_prerounded may fail.
	 */
	if (kalloc_max_prerounded <=  MSG_OOL_SIZE_SMALL_MAX) {
		msg_ool_size_small = kalloc_max_prerounded;
	}
	else {
		msg_ool_size_small = MSG_OOL_SIZE_SMALL_MAX;
	}
	/* account for overhead to avoid spilling over a page */
	msg_ool_size_small -= cpy_kdata_hdr_sz;

	ipc_host_init();
	ux_handler_init();

}