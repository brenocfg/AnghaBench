#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int /*<<< orphan*/  zone_btrecord_t ;
typedef  int /*<<< orphan*/ * zone_btrecord_array_t ;
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_8__ {int /*<<< orphan*/  mzn_name; } ;
typedef  TYPE_2__ mach_zone_name_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ host_priv_t ;
struct TYPE_7__ {int /*<<< orphan*/  zlog_btlog; int /*<<< orphan*/  zone_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_LOGGING (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HOST_NULL ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_HOST ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 TYPE_1__* ZONE_NULL ; 
 int /*<<< orphan*/  all_zones_lock ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ create_vm_map_copy (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  get_btlog_records (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ get_btlog_records_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 scalar_t__ kmem_alloc_pageable (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ num_zones ; 
 scalar_t__ round_page (unsigned int) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ track_this_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_kernel (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* zone_array ; 

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