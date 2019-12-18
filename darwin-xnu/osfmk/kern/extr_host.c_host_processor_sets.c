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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ processor_set_name_array_t ;
typedef  scalar_t__ processor_set_array_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ host_priv_t ;

/* Variables and functions */
 scalar_t__ HOST_PRIV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  convert_pset_name_to_port (int /*<<< orphan*/ *) ; 
 void* kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset0 ; 

kern_return_t
host_processor_sets(host_priv_t host_priv, processor_set_name_array_t * pset_list, mach_msg_type_number_t * count)
{
	void * addr;

	if (host_priv == HOST_PRIV_NULL)
		return (KERN_INVALID_ARGUMENT);

	/*
	 *	Allocate memory.  Can be pageable because it won't be
	 *	touched while holding a lock.
	 */

	addr = kalloc((vm_size_t)sizeof(mach_port_t));
	if (addr == 0)
		return (KERN_RESOURCE_SHORTAGE);

	/* do the conversion that Mig should handle */
	*((ipc_port_t *)addr) = convert_pset_name_to_port(&pset0);

	*pset_list = (processor_set_array_t)addr;
	*count = 1;

	return (KERN_SUCCESS);
}