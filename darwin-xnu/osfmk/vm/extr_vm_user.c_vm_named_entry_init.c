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
 int /*<<< orphan*/  lck_mtx_init_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_named_entry_count ; 
 int /*<<< orphan*/  vm_named_entry_list ; 
 int /*<<< orphan*/  vm_named_entry_list_lock_data ; 
 int /*<<< orphan*/  vm_named_entry_list_lock_data_ext ; 
 int /*<<< orphan*/  vm_object_lck_attr ; 
 int /*<<< orphan*/  vm_object_lck_grp ; 

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