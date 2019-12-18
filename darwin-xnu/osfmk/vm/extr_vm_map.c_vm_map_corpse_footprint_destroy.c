#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
struct vm_map_corpse_footprint_header {scalar_t__ cf_size; } ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {scalar_t__ vmmap_corpse_footprint; scalar_t__ has_corpse_footprint; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  assertf (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
vm_map_corpse_footprint_destroy(
	vm_map_t	map)
{
	if (map->has_corpse_footprint &&
	    map->vmmap_corpse_footprint != 0) {
		struct vm_map_corpse_footprint_header *footprint_header;
		vm_size_t buf_size;
		kern_return_t kr;

		footprint_header = map->vmmap_corpse_footprint;
		buf_size = footprint_header->cf_size;
		kr = vm_deallocate(kernel_map,
				   (vm_offset_t) map->vmmap_corpse_footprint,
				   ((vm_size_t) buf_size
				    + PAGE_SIZE)); /* trailing guard page */
		assertf(kr == KERN_SUCCESS, "kr=0x%x\n", kr);
		map->vmmap_corpse_footprint = 0;
		map->has_corpse_footprint = FALSE;
	}
}