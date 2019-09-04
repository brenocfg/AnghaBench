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
typedef  int /*<<< orphan*/  zone_btrecord_array_t ;
typedef  int /*<<< orphan*/  mach_zone_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 

kern_return_t
mach_zone_get_btlog_records(
	host_priv_t				host,
	mach_zone_name_t		name,
	zone_btrecord_array_t	*recsp,
	mach_msg_type_number_t	*recsCntp)
{
#if DEBUG || DEVELOPMENT
	unsigned int max_zones, i, numrecs = 0;
	zone_btrecord_t *recs;
	kern_return_t kr;
	zone_t zone_ptr;
	vm_offset_t recs_addr;
	vm_size_t recs_size;

	if (host == HOST_NULL)
		return KERN_INVALID_HOST;

	if (recsp == NULL || recsCntp == NULL)
		return KERN_INVALID_ARGUMENT;

	simple_lock(&all_zones_lock);
	max_zones = (unsigned int)(num_zones);
	simple_unlock(&all_zones_lock);

	zone_ptr = ZONE_NULL;
	for (i = 0; i < max_zones; i++) {
		zone_t z = &(zone_array[i]);
		assert(z != ZONE_NULL);

		/* Find the requested zone by name */
		if (track_this_zone(z->zone_name, name.mzn_name)) {
			zone_ptr = z;
			break;
		}
	}

	/* No zones found with the requested zone name */
	if (zone_ptr == ZONE_NULL) {
		return KERN_INVALID_ARGUMENT;
	}

	/* Logging not turned on for the requested zone */
	if (!DO_LOGGING(zone_ptr)) {
		return KERN_FAILURE;
	}

	/* Allocate memory for btlog records */
	numrecs = (unsigned int)(get_btlog_records_count(zone_ptr->zlog_btlog));
	recs_size = round_page(numrecs * sizeof *recs);

	kr = kmem_alloc_pageable(ipc_kernel_map, &recs_addr, recs_size, VM_KERN_MEMORY_IPC);
	if (kr != KERN_SUCCESS) {
		return kr;
	}

	/*
	 * We will call get_btlog_records() below which populates this region while holding a spinlock
	 * (the btlog lock). So these pages need to be wired.
	 */
	kr = vm_map_wire_kernel(ipc_kernel_map, recs_addr, recs_addr + recs_size,
			VM_PROT_READ|VM_PROT_WRITE, VM_KERN_MEMORY_IPC, FALSE);
	assert(kr == KERN_SUCCESS);

	recs = (zone_btrecord_t *)recs_addr;
	get_btlog_records(zone_ptr->zlog_btlog, recs, &numrecs);

	kr = vm_map_unwire(ipc_kernel_map, recs_addr, recs_addr + recs_size, FALSE);
	assert(kr == KERN_SUCCESS);

	*recsp = (zone_btrecord_t *) create_vm_map_copy(recs_addr, recs_size, numrecs * sizeof *recs);
	*recsCntp = numrecs;

	return KERN_SUCCESS;

#else /* DEBUG || DEVELOPMENT */
#pragma unused(host, name, recsp, recsCntp)
	return KERN_FAILURE;
#endif /* DEBUG || DEVELOPMENT */
}