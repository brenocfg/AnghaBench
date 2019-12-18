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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_fault_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
vm_fault(
	vm_map_t	map,
	vm_map_offset_t	vaddr,
	vm_prot_t	fault_type,
	boolean_t	change_wiring,
	vm_tag_t	wire_tag,       	/* if wiring must pass tag != VM_KERN_MEMORY_NONE */
	int		interruptible,
	pmap_t		caller_pmap,
	vm_map_offset_t	caller_pmap_addr)
{
	return vm_fault_internal(map, vaddr, fault_type, change_wiring, wire_tag,
				 interruptible, caller_pmap, caller_pmap_addr,
				 NULL);
}