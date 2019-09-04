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
typedef  int /*<<< orphan*/  mach_zone_name_array_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 

kern_return_t
mach_zone_get_zlog_zones(
	host_priv_t				host,
	mach_zone_name_array_t	*namesp,
	mach_msg_type_number_t  *namesCntp)
{
#if DEBUG || DEVELOPMENT
	unsigned int max_zones, logged_zones, i;
	kern_return_t kr;
	zone_t zone_ptr;
	mach_zone_name_t *names;
	vm_offset_t names_addr;
	vm_size_t names_size;

	if (host == HOST_NULL)
		return KERN_INVALID_HOST;

	if (namesp == NULL || namesCntp == NULL)
		return KERN_INVALID_ARGUMENT;

	simple_lock(&all_zones_lock);
	max_zones = (unsigned int)(num_zones);
	simple_unlock(&all_zones_lock);

	names_size = round_page(max_zones * sizeof *names);
	kr = kmem_alloc_pageable(ipc_kernel_map,
				 &names_addr, names_size, VM_KERN_MEMORY_IPC);
	if (kr != KERN_SUCCESS)
		return kr;
	names = (mach_zone_name_t *) names_addr;

	zone_ptr = ZONE_NULL;
	logged_zones = 0;
	for (i = 0; i < max_zones; i++) {
		zone_t z = &(zone_array[i]);
		assert(z != ZONE_NULL);

		/* Copy out the zone name if zone logging is enabled */
		if(z->zlog_btlog) {
			get_zone_info(z, &names[logged_zones], NULL);
			logged_zones++;
		}
	}

	*namesp = (mach_zone_name_t *) create_vm_map_copy(names_addr, names_size, logged_zones * sizeof *names);
	*namesCntp = logged_zones;

	return KERN_SUCCESS;

#else /* DEBUG || DEVELOPMENT */
#pragma unused(host, namesp, namesCntp)
	return KERN_FAILURE;
#endif /* DEBUG || DEVELOPMENT */
}