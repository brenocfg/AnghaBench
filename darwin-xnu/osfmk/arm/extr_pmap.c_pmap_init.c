#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  copy_strategy; } ;

/* Variables and functions */
 scalar_t__ MAX_ASID ; 
 int /*<<< orphan*/  MEMORY_OBJECT_COPY_NONE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  _vm_object_allocate (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ hard_maxproc ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  mem_size ; 
 int /*<<< orphan*/  pmap_initialized ; 
 TYPE_1__* pmap_object ; 
 int /*<<< orphan*/  pmap_pgtrace_init () ; 
 int /*<<< orphan*/  pmap_zone_init () ; 
 int /*<<< orphan*/  pv_init () ; 
 int /*<<< orphan*/  vm_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_init(
	void)
{
	/*
	 *	Protect page zero in the kernel map.
	 *	(can be overruled by permanent transltion
	 *	table entries at page zero - see arm_vm_init).
	 */
	vm_protect(kernel_map, 0, PAGE_SIZE, TRUE, VM_PROT_NONE);

	pmap_initialized = TRUE;

	pmap_zone_init();


	/*
	 *	Initialize the pmap object (for tracking the vm_page_t
	 *	structures for pages we allocate to be page tables in
	 *	pmap_expand().
	 */
	_vm_object_allocate(mem_size, pmap_object);
	pmap_object->copy_strategy = MEMORY_OBJECT_COPY_NONE;

	pv_init();

	/*
	 * The value of hard_maxproc may have been scaled, make sure
	 * it is still less than the value of MAX_ASID.
	 */
	assert(hard_maxproc < MAX_ASID);

#if CONFIG_PGTRACE
	pmap_pgtrace_init();
#endif
}