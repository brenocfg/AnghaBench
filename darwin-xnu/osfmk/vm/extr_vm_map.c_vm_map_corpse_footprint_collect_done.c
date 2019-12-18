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
typedef  int vm_size_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_address_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vm_map_corpse_footprint_region {scalar_t__ cfr_num_pages; } ;
struct vm_map_corpse_footprint_header {int cf_size; int cf_last_region; scalar_t__ cf_last_zeroes; } ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {int has_corpse_footprint; int /*<<< orphan*/ * vmmap_corpse_footprint; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,struct vm_map_corpse_footprint_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kernel_map ; 
 int round_page (int) ; 
 scalar_t__ vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int vm_map_corpse_footprint_count ; 
 int vm_map_corpse_footprint_size_avg ; 
 int vm_map_corpse_footprint_size_max ; 
 scalar_t__ vm_protect (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_map_corpse_footprint_collect_done(
	vm_map_t	new_map)
{
	struct vm_map_corpse_footprint_header *footprint_header;
	struct vm_map_corpse_footprint_region *footprint_region;
	vm_size_t 	buf_size, actual_size;
	kern_return_t	kr;

	assert(new_map->has_corpse_footprint);
	if (!new_map->has_corpse_footprint ||
	    new_map->vmmap_corpse_footprint == NULL) {
		return;
	}

	footprint_header = (struct vm_map_corpse_footprint_header *)
		new_map->vmmap_corpse_footprint;
	buf_size = footprint_header->cf_size;

	footprint_region = (struct vm_map_corpse_footprint_region *)
		((char *)footprint_header +
		 footprint_header->cf_last_region);

	/* get rid of trailing zeroes in last region */
	assert(footprint_region->cfr_num_pages >= footprint_header->cf_last_zeroes);
	footprint_region->cfr_num_pages -= footprint_header->cf_last_zeroes;
	footprint_header->cf_last_zeroes = 0;

	actual_size = (vm_size_t)(footprint_header->cf_last_region +
				  sizeof (*footprint_region) +
				  footprint_region->cfr_num_pages);

//	printf("FBDP map %p buf_size 0x%llx actual_size 0x%llx\n", new_map, (uint64_t) buf_size, (uint64_t) actual_size);
	vm_map_corpse_footprint_size_avg = 
		(((vm_map_corpse_footprint_size_avg *
		   vm_map_corpse_footprint_count) +
		  actual_size) /
		 (vm_map_corpse_footprint_count + 1));
	vm_map_corpse_footprint_count++;
	if (actual_size > vm_map_corpse_footprint_size_max) {
		vm_map_corpse_footprint_size_max = actual_size;
	}

	actual_size = round_page(actual_size);
	if (buf_size > actual_size) {
		kr = vm_deallocate(kernel_map,
				   ((vm_address_t)footprint_header +
				    actual_size +
				    PAGE_SIZE), /* trailing guard page */
				   (buf_size - actual_size));
		assertf(kr == KERN_SUCCESS,
			"trim: footprint_header %p buf_size 0x%llx actual_size 0x%llx kr=0x%x\n",
			footprint_header,
			(uint64_t) buf_size,
			(uint64_t) actual_size,
			kr);
		kr = vm_protect(kernel_map,
				((vm_address_t)footprint_header +
				 actual_size),
				PAGE_SIZE,
				FALSE, /* set_maximum */
				VM_PROT_NONE);
		assertf(kr == KERN_SUCCESS,
			"guard: footprint_header %p buf_size 0x%llx actual_size 0x%llx kr=0x%x\n",
			footprint_header,
			(uint64_t) buf_size,
			(uint64_t) actual_size,
			kr);
	}

	footprint_header->cf_size = actual_size;
}