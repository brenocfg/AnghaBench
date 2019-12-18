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
typedef  int /*<<< orphan*/  vm_phantom_hash_entry_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  unsigned int uint32_t ;
struct vm_ghost {int dummy; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int KMA_KOBJECT ; 
 int KMA_PERMANENT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_CONFIG_COMPRESSOR_IS_ACTIVE ; 
 int VM_GHOST_PAGES_PER_ENTRY ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_PHANTOM_CACHE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kernel_memory_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int max_mem ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int vm_ghost_bucket_hash ; 
 unsigned int vm_ghost_hash_mask ; 
 int /*<<< orphan*/  vm_phantom_cache ; 
 int /*<<< orphan*/  vm_phantom_cache_hash ; 
 int vm_phantom_cache_hash_size ; 
 unsigned int vm_phantom_cache_num_entries ; 
 int vm_phantom_cache_size ; 

void
vm_phantom_cache_init()
{
	unsigned int	num_entries;
	unsigned int	log1;
	unsigned int	size;

	if ( !VM_CONFIG_COMPRESSOR_IS_ACTIVE)
		return;
#if CONFIG_EMBEDDED
	num_entries = (uint32_t)(((max_mem / PAGE_SIZE) / 10) / VM_GHOST_PAGES_PER_ENTRY);
#else
	num_entries = (uint32_t)(((max_mem / PAGE_SIZE) / 4) / VM_GHOST_PAGES_PER_ENTRY);
#endif
	vm_phantom_cache_num_entries = 1;

	while (vm_phantom_cache_num_entries < num_entries)
		vm_phantom_cache_num_entries <<= 1;

	vm_phantom_cache_size = sizeof(struct vm_ghost) * vm_phantom_cache_num_entries;
	vm_phantom_cache_hash_size = sizeof(vm_phantom_hash_entry_t) * vm_phantom_cache_num_entries;

	if (kernel_memory_allocate(kernel_map, (vm_offset_t *)(&vm_phantom_cache), vm_phantom_cache_size, 0, KMA_KOBJECT | KMA_PERMANENT, VM_KERN_MEMORY_PHANTOM_CACHE) != KERN_SUCCESS)
		panic("vm_phantom_cache_init: kernel_memory_allocate failed\n");
	bzero(vm_phantom_cache, vm_phantom_cache_size);

	if (kernel_memory_allocate(kernel_map, (vm_offset_t *)(&vm_phantom_cache_hash), vm_phantom_cache_hash_size, 0, KMA_KOBJECT | KMA_PERMANENT, VM_KERN_MEMORY_PHANTOM_CACHE) != KERN_SUCCESS)
		panic("vm_phantom_cache_init: kernel_memory_allocate failed\n");
	bzero(vm_phantom_cache_hash, vm_phantom_cache_hash_size);


	vm_ghost_hash_mask = vm_phantom_cache_num_entries - 1;

	/*
	 *	Calculate object_id shift value for hashing algorithm:
	 *		O = log2(sizeof(struct vm_object))
	 *		B = log2(vm_page_bucket_count)
	 *	        hash shifts the object_id left by
	 *		B/2 - O
	 */
	size = vm_phantom_cache_num_entries;
	for (log1 = 0; size > 1; log1++) 
		size /= 2;
	
	vm_ghost_bucket_hash = 1 << ((log1 + 1) >> 1);		/* Get (ceiling of sqrt of table size) */
	vm_ghost_bucket_hash |= 1 << ((log1 + 1) >> 2);		/* Get (ceiling of quadroot of table size) */
	vm_ghost_bucket_hash |= 1;				/* Set bit and add 1 - always must be 1 to insure unique series */

	if (vm_ghost_hash_mask & vm_phantom_cache_num_entries)
		printf("vm_phantom_cache_init: WARNING -- strange page hash\n");
}