#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  vmkf_permanent; } ;
typedef  TYPE_1__ vm_map_kernel_flags_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_ZONE ; 
 TYPE_1__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  gzalloc_map ; 
 scalar_t__ gzalloc_map_max ; 
 scalar_t__ gzalloc_map_min ; 
 scalar_t__ gzalloc_mode ; 
 int gzalloc_zonemap_scale ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_suballoc (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 

void gzalloc_init(vm_size_t max_zonemap_size) {
	kern_return_t retval;

	if (gzalloc_mode) {
		vm_map_kernel_flags_t vmk_flags;

		vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
		vmk_flags.vmkf_permanent = TRUE;
		retval = kmem_suballoc(kernel_map, &gzalloc_map_min, (max_zonemap_size * gzalloc_zonemap_scale),
				       FALSE, VM_FLAGS_ANYWHERE, vmk_flags, VM_KERN_MEMORY_ZONE,
				       &gzalloc_map);
	
		if (retval != KERN_SUCCESS) {
			panic("zone_init: kmem_suballoc(gzalloc_map, 0x%lx, %u) failed", max_zonemap_size, gzalloc_zonemap_scale);
		}
		gzalloc_map_max = gzalloc_map_min + (max_zonemap_size * gzalloc_zonemap_scale);
	}
}