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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  int /*<<< orphan*/  task_t ;
struct proc {int /*<<< orphan*/  task; } ;
struct dtrace_ptss_page {TYPE_1__* entries; } ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  void* mach_vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_2__ {struct TYPE_2__* next; void* write_addr; void* addr; } ;

/* Variables and functions */
 int DTRACE_PTSS_ENTRIES_PER_PAGE ; 
 int DTRACE_PTSS_SCRATCH_SPACE_PER_THREAD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_PORT_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PAGE_MAX_SIZE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  _FREE (struct dtrace_ptss_page*,int /*<<< orphan*/ ) ; 
 struct dtrace_ptss_page* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_task_map_reference (int /*<<< orphan*/ ) ; 
 scalar_t__ mach_vm_map_kernel (int /*<<< orphan*/ *,void**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_vm_protect (int /*<<< orphan*/ *,void*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mach_vm_remap_kernel (int /*<<< orphan*/ *,void**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ *) ; 

struct dtrace_ptss_page*
dtrace_ptss_allocate_page(struct proc* p)
{
	// Allocate the kernel side data
	struct dtrace_ptss_page* ptss_page = _MALLOC(sizeof(struct dtrace_ptss_page), M_TEMP, M_ZERO | M_WAITOK);
	if (ptss_page == NULL)
		return NULL;

	// Now allocate a page in user space and set its protections to allow execute.
	task_t task = p->task;
	vm_map_t map = get_task_map_reference(task);
	if (map == NULL)
	  goto err;

	mach_vm_size_t size = PAGE_MAX_SIZE;
	mach_vm_offset_t addr = 0;
	mach_vm_offset_t write_addr = 0;
	/* 
	 * The embedded OS has extra permissions for writable and executable pages.
	 * To ensure correct permissions, we must set the page protections separately.
	 */
	vm_prot_t cur_protection = VM_PROT_READ|VM_PROT_EXECUTE;
	vm_prot_t max_protection = VM_PROT_READ|VM_PROT_EXECUTE|VM_PROT_WRITE;

	kern_return_t kr = mach_vm_map_kernel(map, &addr, size, 0, VM_FLAGS_ANYWHERE, VM_MAP_KERNEL_FLAGS_NONE, VM_KERN_MEMORY_NONE, IPC_PORT_NULL, 0, FALSE, cur_protection, max_protection, VM_INHERIT_DEFAULT);
	if (kr != KERN_SUCCESS) {
		goto err;
	}
	/*
	 * If on embedded, remap the scratch space as writable at another
	 * virtual address
	 */
	 kr = mach_vm_remap_kernel(map, &write_addr, size, 0, VM_FLAGS_ANYWHERE, VM_KERN_MEMORY_NONE, map, addr, FALSE, &cur_protection, &max_protection, VM_INHERIT_DEFAULT);
	if (kr != KERN_SUCCESS || !(max_protection & VM_PROT_WRITE))
		goto err;

	kr = mach_vm_protect (map, (mach_vm_offset_t)write_addr, (mach_vm_size_t)size, 0, VM_PROT_READ | VM_PROT_WRITE);
	if (kr != KERN_SUCCESS)
		goto err;

	// Chain the page entries.
	int i;
	for (i=0; i<DTRACE_PTSS_ENTRIES_PER_PAGE; i++) {
		ptss_page->entries[i].addr = addr + (i * DTRACE_PTSS_SCRATCH_SPACE_PER_THREAD);
		ptss_page->entries[i].write_addr = write_addr + (i * DTRACE_PTSS_SCRATCH_SPACE_PER_THREAD);
		ptss_page->entries[i].next = &ptss_page->entries[i+1];
	}

	// The last entry should point to NULL
	ptss_page->entries[DTRACE_PTSS_ENTRIES_PER_PAGE-1].next = NULL;

	vm_map_deallocate(map);

	return ptss_page;

err:
	_FREE(ptss_page, M_TEMP);

	if (map)
	  vm_map_deallocate(map);

	return NULL;
}