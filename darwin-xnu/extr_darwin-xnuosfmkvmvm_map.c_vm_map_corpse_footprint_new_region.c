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
typedef  int uint32_t ;
struct vm_map_corpse_footprint_region {scalar_t__ cfr_num_pages; scalar_t__ cfr_vaddr; } ;
struct vm_map_corpse_footprint_header {uintptr_t cf_size; uintptr_t cf_last_region; scalar_t__ cf_last_zeroes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int roundup (int,int) ; 

__attribute__((used)) static struct vm_map_corpse_footprint_region *
vm_map_corpse_footprint_new_region(
	struct vm_map_corpse_footprint_header *footprint_header)
{
	uintptr_t	footprint_edge;
	uint32_t	new_region_offset;
	struct vm_map_corpse_footprint_region *footprint_region;
	struct vm_map_corpse_footprint_region *new_footprint_region;

	footprint_edge = ((uintptr_t)footprint_header +
			  footprint_header->cf_size);
	footprint_region = ((struct vm_map_corpse_footprint_region *)
			    ((char *)footprint_header +
			     footprint_header->cf_last_region));
	assert((uintptr_t)footprint_region + sizeof (*footprint_region) <=
	       footprint_edge);

	/* get rid of trailing zeroes in the last region */
	assert(footprint_region->cfr_num_pages >=
	       footprint_header->cf_last_zeroes);
	footprint_region->cfr_num_pages -=
			footprint_header->cf_last_zeroes;
	footprint_header->cf_last_zeroes = 0;

	/* reuse this region if it's now empty */
	if (footprint_region->cfr_num_pages == 0) {
		return footprint_region;
	}

	/* compute offset of new region */
	new_region_offset = footprint_header->cf_last_region;
	new_region_offset += sizeof (*footprint_region);
	new_region_offset += footprint_region->cfr_num_pages;
	new_region_offset = roundup(new_region_offset, sizeof (int));

	/* check if we're going over the edge */
	if (((uintptr_t)footprint_header +
	     new_region_offset +
	     sizeof (*footprint_region)) >=
	    footprint_edge) {
		/* over the edge: no new region */
		return NULL;
	}

	/* adjust offset of last region in header */
	footprint_header->cf_last_region = new_region_offset;

	new_footprint_region = (struct vm_map_corpse_footprint_region *)
		((char *)footprint_header +
		 footprint_header->cf_last_region);
	new_footprint_region->cfr_vaddr = 0;
	new_footprint_region->cfr_num_pages = 0;
	/* caller needs to initialize new region */

	return new_footprint_region;
}