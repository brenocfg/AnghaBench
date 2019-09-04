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

/* Variables and functions */

void
vm_named_entry_init(void)
{
#if VM_NAMED_ENTRY_LIST
	queue_init(&vm_named_entry_list);
	vm_named_entry_count = 0;
	lck_mtx_init_ext(&vm_named_entry_list_lock_data,
			 &vm_named_entry_list_lock_data_ext,
			 &vm_object_lck_grp,
			 &vm_object_lck_attr);
#endif /* VM_NAMED_ENTRY_LIST */
}