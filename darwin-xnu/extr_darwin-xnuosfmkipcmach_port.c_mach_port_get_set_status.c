#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  scalar_t__ vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_pset_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  int ipc_entry_num_t ;
struct TYPE_6__ {int /*<<< orphan*/  ips_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_PORT_SET ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 scalar_t__ VM_MAP_COPY_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int VM_MAP_PAGE_SIZE (int /*<<< orphan*/ ) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 int /*<<< orphan*/  ipc_mqueue_set_gather_member_names (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ipc_object_translate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ips_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ vm_allocate_kernel (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vm_map_round_page (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_kernel (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_get_set_status(
	ipc_space_t			space,
	mach_port_name_t		name,
	mach_port_name_t		**members,
	mach_msg_type_number_t		*membersCnt)
{
	ipc_entry_num_t actual;		/* this many members */
	ipc_entry_num_t maxnames;	/* space for this many members */
	kern_return_t kr;

	vm_size_t size;		/* size of allocated memory */
	vm_offset_t addr;	/* allocated memory */
	vm_map_copy_t memory;	/* copied-in memory */

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(name))
		return KERN_INVALID_RIGHT;

	size = VM_MAP_PAGE_SIZE(ipc_kernel_map);	/* initial guess */

	for (;;) {
		mach_port_name_t *names;
		ipc_object_t psobj;
		ipc_pset_t pset;

		kr = vm_allocate_kernel(ipc_kernel_map, &addr, size, VM_FLAGS_ANYWHERE, VM_KERN_MEMORY_IPC);
		if (kr != KERN_SUCCESS)
			return KERN_RESOURCE_SHORTAGE;

		/* can't fault while we hold locks */

		kr = vm_map_wire_kernel(ipc_kernel_map, addr, addr + size,
				     VM_PROT_READ|VM_PROT_WRITE, VM_KERN_MEMORY_IPC, FALSE);
		assert(kr == KERN_SUCCESS);

		kr = ipc_object_translate(space, name, MACH_PORT_RIGHT_PORT_SET, &psobj);
		if (kr != KERN_SUCCESS) {
			kmem_free(ipc_kernel_map, addr, size);
			return kr;
		}

		/* just use a portset reference from here on out */
		__IGNORE_WCASTALIGN(pset = (ipc_pset_t) psobj);
		ips_reference(pset);
		ips_unlock(pset); 

		names = (mach_port_name_t *) addr;
		maxnames = (ipc_entry_num_t)(size / sizeof(mach_port_name_t));

		ipc_mqueue_set_gather_member_names(space, &pset->ips_messages, maxnames, names, &actual);

		/* release the portset reference */
		ips_release(pset);

		if (actual <= maxnames)
			break;

		/* didn't have enough memory; allocate more */
		kmem_free(ipc_kernel_map, addr, size);
		size = vm_map_round_page(
			(actual * sizeof(mach_port_name_t)),
			 VM_MAP_PAGE_MASK(ipc_kernel_map)) +
			VM_MAP_PAGE_SIZE(ipc_kernel_map);
	}

	if (actual == 0) {
		memory = VM_MAP_COPY_NULL;

		kmem_free(ipc_kernel_map, addr, size);
	} else {
		vm_size_t size_used;
		vm_size_t vm_size_used;

		size_used = actual * sizeof(mach_port_name_t);
		vm_size_used = vm_map_round_page(
			size_used,
			VM_MAP_PAGE_MASK(ipc_kernel_map));

		/*
		 *	Make used memory pageable and get it into
		 *	copied-in form.  Free any unused memory.
		 */

		kr = vm_map_unwire(
			ipc_kernel_map,
			vm_map_trunc_page(addr,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)), 
			vm_map_round_page(addr + vm_size_used,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			FALSE);
		assert(kr == KERN_SUCCESS);

		kr = vm_map_copyin(ipc_kernel_map, (vm_map_address_t)addr,
				   (vm_map_size_t)size_used, TRUE, &memory);
		assert(kr == KERN_SUCCESS);

		if (vm_size_used != size)
			kmem_free(ipc_kernel_map,
				  addr + vm_size_used, size - vm_size_used);
	}

	*members = (mach_port_name_t *) memory;
	*membersCnt = actual;
	return KERN_SUCCESS;
}