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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int VM_MAP_CREATE_PAGEABLE ; 
 int /*<<< orphan*/  vm_map_create_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

vm_map_t
vm_map_create(
	pmap_t		pmap,
	vm_map_offset_t	min,
	vm_map_offset_t	max,
	boolean_t	pageable)
{
	int options;

	options = 0;
	if (pageable) {
		options |= VM_MAP_CREATE_PAGEABLE;
	}
	return vm_map_create_options(pmap, min, max, options);
}