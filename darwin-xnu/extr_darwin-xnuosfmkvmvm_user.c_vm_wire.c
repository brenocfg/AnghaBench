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
typedef  scalar_t__ vm_size_t ;
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/ * host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HOST_PRIV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_HOST ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_OSFMK ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (scalar_t__) ; 
 int VM_PROT_ALL ; 
 int VM_PROT_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  realhost ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unwire (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_wire_kernel (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
vm_wire(
	host_priv_t		host_priv,
	vm_map_t		map,
	vm_offset_t		start,
	vm_size_t		size,
	vm_prot_t		access)
{
	kern_return_t		rc;

	if (host_priv == HOST_PRIV_NULL)
		return KERN_INVALID_HOST;

	assert(host_priv == &realhost);

	if (map == VM_MAP_NULL)
		return KERN_INVALID_TASK;

	if ((access & ~VM_PROT_ALL) || (start + size < start))
		return KERN_INVALID_ARGUMENT;

	if (size == 0) {
		rc = KERN_SUCCESS;
	} else if (access != VM_PROT_NONE) {
		rc = vm_map_wire_kernel(map,
				 vm_map_trunc_page(start,
						   VM_MAP_PAGE_MASK(map)),
				 vm_map_round_page(start+size,
						   VM_MAP_PAGE_MASK(map)),
				 access, VM_KERN_MEMORY_OSFMK,
				 TRUE);
	} else {
		rc = vm_map_unwire(map,
				   vm_map_trunc_page(start,
						     VM_MAP_PAGE_MASK(map)),
				   vm_map_round_page(start+size,
						     VM_MAP_PAGE_MASK(map)),
				   TRUE);
	}
	return rc;
}