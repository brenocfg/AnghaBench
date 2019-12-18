#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  task_t ;
struct proc {int /*<<< orphan*/  task; } ;
struct dtrace_ptss_page {TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
struct TYPE_2__ {int /*<<< orphan*/  write_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  get_task_map_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 

void
dtrace_ptss_free_page(struct proc* p, struct dtrace_ptss_page* ptss_page)
{
	// Grab the task and get a reference to its vm_map
	task_t task = p->task;
	vm_map_t map = get_task_map_reference(task);

	mach_vm_address_t addr = ptss_page->entries[0].addr;
	mach_vm_size_t size = PAGE_SIZE; // We need some way to assert that this matches vm_map_round_page() !!!

	// Silent failures, no point in checking return code.
	mach_vm_deallocate(map, addr, size);

	mach_vm_address_t write_addr = ptss_page->entries[0].write_addr;
	mach_vm_deallocate(map, write_addr, size);

	vm_map_deallocate(map);
}