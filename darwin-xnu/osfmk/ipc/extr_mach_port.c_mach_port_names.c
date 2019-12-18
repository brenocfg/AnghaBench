#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  scalar_t__ vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int mach_port_index_t ;
typedef  int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_timestamp_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int ipc_entry_num_t ;
typedef  int /*<<< orphan*/  ipc_entry_bits_t ;
struct TYPE_10__ {int /*<<< orphan*/  ie_bits; } ;
struct TYPE_9__ {int is_table_size; TYPE_2__* is_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IE_BITS_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* IS_NULL ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_MAKE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 scalar_t__ VM_MAP_COPY_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 int /*<<< orphan*/  ipc_port_timestamp () ; 
 int /*<<< orphan*/  is_active (TYPE_1__*) ; 
 int /*<<< orphan*/  is_read_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  is_read_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mach_port_names_helper (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  static_assert (int) ; 
 scalar_t__ vm_allocate_kernel (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_names(
	ipc_space_t		space,
	mach_port_name_t	**namesp,
	mach_msg_type_number_t	*namesCnt,
	mach_port_type_t	**typesp,
	mach_msg_type_number_t	*typesCnt)
{
	ipc_entry_t table;
	ipc_entry_num_t tsize;
	mach_port_index_t index;
	ipc_entry_num_t actual;	/* this many names */
	ipc_port_timestamp_t timestamp;	/* logical time of this operation */
	mach_port_name_t *names;
	mach_port_type_t *types;
	kern_return_t kr;

	vm_size_t size;		/* size of allocated memory */
	vm_offset_t addr1;	/* allocated memory, for names */
	vm_offset_t addr2;	/* allocated memory, for types */
	vm_map_copy_t memory1;	/* copied-in memory, for names */
	vm_map_copy_t memory2;	/* copied-in memory, for types */

	/* safe simplifying assumption */
	static_assert(sizeof(mach_port_name_t) == sizeof(mach_port_type_t));

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	size = 0;

	for (;;) {
		ipc_entry_num_t bound;
		vm_size_t size_needed;

		is_read_lock(space);
		if (!is_active(space)) {
			is_read_unlock(space);
			if (size != 0) {
				kmem_free(ipc_kernel_map, addr1, size);
				kmem_free(ipc_kernel_map, addr2, size);
			}
			return KERN_INVALID_TASK;
		}

		/* upper bound on number of names in the space */
		bound = space->is_table_size;
		size_needed = vm_map_round_page(
			(bound * sizeof(mach_port_name_t)),
			VM_MAP_PAGE_MASK(ipc_kernel_map));

		if (size_needed <= size)
			break;

		is_read_unlock(space);

		if (size != 0) {
			kmem_free(ipc_kernel_map, addr1, size);
			kmem_free(ipc_kernel_map, addr2, size);
		}
		size = size_needed;

		kr = vm_allocate_kernel(ipc_kernel_map, &addr1, size, VM_FLAGS_ANYWHERE, VM_KERN_MEMORY_IPC);
		if (kr != KERN_SUCCESS)
			return KERN_RESOURCE_SHORTAGE;

		kr = vm_allocate_kernel(ipc_kernel_map, &addr2, size, VM_FLAGS_ANYWHERE, VM_KERN_MEMORY_IPC);
		if (kr != KERN_SUCCESS) {
			kmem_free(ipc_kernel_map, addr1, size);
			return KERN_RESOURCE_SHORTAGE;
		}

		/* can't fault while we hold locks */

		kr = vm_map_wire_kernel(
			ipc_kernel_map,
			vm_map_trunc_page(addr1,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			vm_map_round_page(addr1 + size,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			VM_PROT_READ|VM_PROT_WRITE, VM_KERN_MEMORY_IPC,
			FALSE);
		if (kr != KERN_SUCCESS) {
			kmem_free(ipc_kernel_map, addr1, size);
			kmem_free(ipc_kernel_map, addr2, size);
			return KERN_RESOURCE_SHORTAGE;
		}

		kr = vm_map_wire_kernel(
			ipc_kernel_map,
			vm_map_trunc_page(addr2,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			vm_map_round_page(addr2 + size,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			VM_PROT_READ|VM_PROT_WRITE,
			VM_KERN_MEMORY_IPC,
			FALSE);
		if (kr != KERN_SUCCESS) {
			kmem_free(ipc_kernel_map, addr1, size);
			kmem_free(ipc_kernel_map, addr2, size);
			return KERN_RESOURCE_SHORTAGE;
		}

	}
	/* space is read-locked and active */

	names = (mach_port_name_t *) addr1;
	types = (mach_port_type_t *) addr2;
	actual = 0;

	timestamp = ipc_port_timestamp();

	table = space->is_table;
	tsize = space->is_table_size;

	for (index = 0; index < tsize; index++) {
		ipc_entry_t entry = &table[index];
		ipc_entry_bits_t bits = entry->ie_bits;

		if (IE_BITS_TYPE(bits) != MACH_PORT_TYPE_NONE) {
			mach_port_name_t name;

			name = MACH_PORT_MAKE(index, IE_BITS_GEN(bits));
			mach_port_names_helper(timestamp, entry, name, names,
					       types, &actual);
		}
	}

	is_read_unlock(space);

	if (actual == 0) {
		memory1 = VM_MAP_COPY_NULL;
		memory2 = VM_MAP_COPY_NULL;

		if (size != 0) {
			kmem_free(ipc_kernel_map, addr1, size);
			kmem_free(ipc_kernel_map, addr2, size);
		}
	} else {
		vm_size_t size_used;
		vm_size_t vm_size_used;

		size_used = actual * sizeof(mach_port_name_t);
		vm_size_used =
			vm_map_round_page(size_used,
					  VM_MAP_PAGE_MASK(ipc_kernel_map));

		/*
		 *	Make used memory pageable and get it into
		 *	copied-in form.  Free any unused memory.
		 */

		kr = vm_map_unwire(
			ipc_kernel_map,
			vm_map_trunc_page(addr1,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			vm_map_round_page(addr1 + vm_size_used,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			FALSE);
		assert(kr == KERN_SUCCESS);

		kr = vm_map_unwire(
			ipc_kernel_map,
			vm_map_trunc_page(addr2,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			vm_map_round_page(addr2 + vm_size_used,
					  VM_MAP_PAGE_MASK(ipc_kernel_map)),
			FALSE);
		assert(kr == KERN_SUCCESS);

		kr = vm_map_copyin(ipc_kernel_map, (vm_map_address_t)addr1,
				   (vm_map_size_t)size_used, TRUE, &memory1);
		assert(kr == KERN_SUCCESS);

		kr = vm_map_copyin(ipc_kernel_map, (vm_map_address_t)addr2,
				   (vm_map_size_t)size_used, TRUE, &memory2);
		assert(kr == KERN_SUCCESS);

		if (vm_size_used != size) {
			kmem_free(ipc_kernel_map,
				  addr1 + vm_size_used, size - vm_size_used);
			kmem_free(ipc_kernel_map,
				  addr2 + vm_size_used, size - vm_size_used);
		}
	}

	*namesp = (mach_port_name_t *) memory1;
	*namesCnt = actual;
	*typesp = (mach_port_type_t *) memory2;
	*typesCnt = actual;
	return KERN_SUCCESS;
}