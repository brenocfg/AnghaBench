#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  TYPE_2__* vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  TYPE_3__* thread_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_17__ {TYPE_1__* map; } ;
struct TYPE_16__ {scalar_t__ size; int /*<<< orphan*/  cpy_kdata; scalar_t__ offset; } ;
struct TYPE_15__ {scalar_t__ pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_INVALID_ADDRESS ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_FLAGS ; 
 int /*<<< orphan*/  VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ copyout (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ cpy_kdata_hdr_sz ; 
 TYPE_3__* current_thread () ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,scalar_t__) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  kfree (TYPE_2__*,scalar_t__) ; 
 scalar_t__ msg_ool_size_small ; 
 int /*<<< orphan*/  panic (char*,long long,long long) ; 
 int /*<<< orphan*/  vm_map_copyout_kernel_buffer_failures ; 
 int /*<<< orphan*/  vm_map_deallocate (TYPE_1__*) ; 
 scalar_t__ vm_map_enter (TYPE_1__*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_remove (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_switch (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vm_map_copyout_kernel_buffer(
	vm_map_t		map,
	vm_map_address_t	*addr,	/* IN/OUT */
	vm_map_copy_t		copy,
	vm_map_size_t		copy_size,
	boolean_t		overwrite,
	boolean_t		consume_on_success)
{
	kern_return_t kr = KERN_SUCCESS;
	thread_t thread = current_thread();

	assert(copy->size == copy_size);

	/*
	 * check for corrupted vm_map_copy structure
	 */
	if (copy_size > msg_ool_size_small || copy->offset)
		panic("Invalid vm_map_copy_t sz:%lld, ofst:%lld",
		      (long long)copy->size, (long long)copy->offset);

	if (!overwrite) {

		/*
		 * Allocate space in the target map for the data
		 */
		*addr = 0;
		kr = vm_map_enter(map,
				  addr,
				  vm_map_round_page(copy_size,
						    VM_MAP_PAGE_MASK(map)),
				  (vm_map_offset_t) 0,
				  VM_FLAGS_ANYWHERE,
				  VM_MAP_KERNEL_FLAGS_NONE,
				  VM_KERN_MEMORY_NONE,
				  VM_OBJECT_NULL,
				  (vm_object_offset_t) 0,
				  FALSE,
				  VM_PROT_DEFAULT,
				  VM_PROT_ALL,
				  VM_INHERIT_DEFAULT);
		if (kr != KERN_SUCCESS)
			return kr;
#if KASAN
		if (map->pmap == kernel_pmap) {
			kasan_notify_address(*addr, copy->size);
		}
#endif
	}

	/*
	 * Copyout the data from the kernel buffer to the target map.
	 */
	if (thread->map == map) {

		/*
		 * If the target map is the current map, just do
		 * the copy.
		 */
		assert((vm_size_t)copy_size == copy_size);
		if (copyout(copy->cpy_kdata, *addr, (vm_size_t)copy_size)) {
			kr = KERN_INVALID_ADDRESS;
		}
	}
	else {
		vm_map_t oldmap;

		/*
		 * If the target map is another map, assume the
		 * target's address space identity for the duration
		 * of the copy.
		 */
		vm_map_reference(map);
		oldmap = vm_map_switch(map);

		assert((vm_size_t)copy_size == copy_size);
		if (copyout(copy->cpy_kdata, *addr, (vm_size_t)copy_size)) {
			vm_map_copyout_kernel_buffer_failures++;
			kr = KERN_INVALID_ADDRESS;
		}

		(void) vm_map_switch(oldmap);
		vm_map_deallocate(map);
	}

	if (kr != KERN_SUCCESS) {
		/* the copy failed, clean up */
		if (!overwrite) {
			/*
			 * Deallocate the space we allocated in the target map.
			 */
			(void) vm_map_remove(
				map,
				vm_map_trunc_page(*addr,
						  VM_MAP_PAGE_MASK(map)),
				vm_map_round_page((*addr +
						   vm_map_round_page(copy_size,
								     VM_MAP_PAGE_MASK(map))),
						  VM_MAP_PAGE_MASK(map)),
				VM_MAP_REMOVE_NO_FLAGS);
			*addr = 0;
		}
	} else {
		/* copy was successful, dicard the copy structure */
		if (consume_on_success) {
			kfree(copy, copy_size + cpy_kdata_hdr_sz);
		}
	}

	return kr;
}