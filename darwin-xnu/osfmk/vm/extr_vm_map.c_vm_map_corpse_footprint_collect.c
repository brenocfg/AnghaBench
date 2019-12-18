#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  int vm_map_offset_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vm_map_corpse_footprint_region {scalar_t__ cfr_vaddr; int cfr_num_pages; } ;
struct vm_map_corpse_footprint_header {int cf_size; int cf_last_region; int cf_last_zeroes; } ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_15__ {int vme_start; int vme_end; scalar_t__ iokit_acct; int /*<<< orphan*/  is_sub_map; } ;
struct TYPE_12__ {int nentries; } ;
struct TYPE_14__ {int has_corpse_footprint; int size; int /*<<< orphan*/  pmap; struct vm_map_corpse_footprint_header* vmmap_corpse_footprint; TYPE_1__ hdr; } ;
struct TYPE_13__ {scalar_t__ purgable; scalar_t__ internal; } ;

/* Variables and functions */
 scalar_t__ KERN_NOT_SUPPORTED ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int KMA_GUARD_LAST ; 
 int KMA_PAGEABLE ; 
 int PAGE_SIZE ; 
 int PMAP_QUERY_PAGE_INTERNAL ; 
 int PMAP_QUERY_PAGE_PRESENT ; 
 TYPE_2__* VME_OBJECT (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int VM_MAP_CORPSE_FOOTPRINT_INFO_MAX_SIZE ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kernel_memory_allocate (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ os_add3_overflow (int,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ os_add_overflow (int,int,scalar_t__*) ; 
 int /*<<< orphan*/  pmap_query_page_info (int /*<<< orphan*/ ,int,int*) ; 
 int round_page (int) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  vm_map_corpse_footprint_full ; 
 struct vm_map_corpse_footprint_region* vm_map_corpse_footprint_new_region (struct vm_map_corpse_footprint_header*) ; 
 int /*<<< orphan*/  vm_map_corpse_footprint_no_buf ; 
 int /*<<< orphan*/  vm_map_lock_assert_exclusive (TYPE_3__*) ; 

kern_return_t
vm_map_corpse_footprint_collect(
	vm_map_t	old_map,
	vm_map_entry_t	old_entry,
	vm_map_t	new_map)
{
	vm_map_offset_t	va;
	int 		disp;
	kern_return_t	kr;
	struct vm_map_corpse_footprint_header *footprint_header;
	struct vm_map_corpse_footprint_region *footprint_region;
	struct vm_map_corpse_footprint_region *new_footprint_region;
	unsigned char	*next_disp_p;
	uintptr_t	footprint_edge;
	uint32_t	num_pages_tmp;

	va = old_entry->vme_start;

	vm_map_lock_assert_exclusive(old_map);
	vm_map_lock_assert_exclusive(new_map);

	assert(new_map->has_corpse_footprint);
	assert(!old_map->has_corpse_footprint);
	if (!new_map->has_corpse_footprint ||
	    old_map->has_corpse_footprint) {
		/*
		 * This can only transfer footprint info from a
		 * map with a live pmap to a map with a corpse footprint.
		 */
		return KERN_NOT_SUPPORTED;
	}

	if (new_map->vmmap_corpse_footprint == NULL) {
		vm_offset_t	buf;
		vm_size_t	buf_size;

		buf = 0;
		buf_size = (sizeof (*footprint_header) +
			    (old_map->hdr.nentries
			     *
			     (sizeof (*footprint_region) +
			      + 3)) /* potential alignment for each region */
			    +
			    ((old_map->size / PAGE_SIZE)
			     *
			     sizeof (char))); /* disposition for each page */
//		printf("FBDP corpse map %p guestimate footprint size 0x%llx\n", new_map, (uint64_t) buf_size);
		buf_size = round_page(buf_size);

		/* limit buffer to 1 page to validate overflow detection */
//		buf_size = PAGE_SIZE;

		/* limit size to a somewhat sane amount */
#if CONFIG_EMBEDDED
#define VM_MAP_CORPSE_FOOTPRINT_INFO_MAX_SIZE	(256*1024)	/* 256KB */
#else /* CONFIG_EMBEDDED */
#define VM_MAP_CORPSE_FOOTPRINT_INFO_MAX_SIZE	(8*1024*1024)	/* 8MB */
#endif /* CONFIG_EMBEDDED */
		if (buf_size > VM_MAP_CORPSE_FOOTPRINT_INFO_MAX_SIZE) {
			buf_size = VM_MAP_CORPSE_FOOTPRINT_INFO_MAX_SIZE;
		}

		/*
		 * Allocate the pageable buffer (with a trailing guard page).
		 * It will be zero-filled on demand.
		 */
		kr = kernel_memory_allocate(kernel_map,
					    &buf,
					    (buf_size
					     + PAGE_SIZE), /* trailing guard page */
					    0, /* mask */
					    KMA_PAGEABLE | KMA_GUARD_LAST,
					    VM_KERN_MEMORY_DIAG);
		if (kr != KERN_SUCCESS) {
			vm_map_corpse_footprint_no_buf++;
			return kr;
		}

		/* initialize header and 1st region */
		footprint_header = (struct vm_map_corpse_footprint_header *)buf;
		new_map->vmmap_corpse_footprint = footprint_header;

		footprint_header->cf_size = buf_size;
		footprint_header->cf_last_region =
			sizeof (*footprint_header);
		footprint_header->cf_last_zeroes = 0;

		footprint_region = (struct vm_map_corpse_footprint_region *)
			((char *)footprint_header +
			 footprint_header->cf_last_region);
		footprint_region->cfr_vaddr = 0;
		footprint_region->cfr_num_pages = 0;
	} else {
		/* retrieve header and last region */
		footprint_header = (struct vm_map_corpse_footprint_header *)
			new_map->vmmap_corpse_footprint;
		footprint_region = (struct vm_map_corpse_footprint_region *)
			((char *)footprint_header +
			 footprint_header->cf_last_region);
	}
	footprint_edge = ((uintptr_t)footprint_header +
			  footprint_header->cf_size);

	if ((footprint_region->cfr_vaddr +
	     (((vm_map_offset_t)footprint_region->cfr_num_pages) *
	      PAGE_SIZE))
	    != old_entry->vme_start) {
		uint64_t num_pages_delta;
		uint32_t region_offset_delta;

		/*
		 * Not the next contiguous virtual address:
		 * start a new region or store "zero" dispositions for
		 * the missing pages?
		 */
		/* size of gap in actual page dispositions */
		num_pages_delta = (((old_entry->vme_start -
				     footprint_region->cfr_vaddr) / PAGE_SIZE)
				   - footprint_region->cfr_num_pages);
		/* size of gap as a new footprint region header */
		region_offset_delta =
			(sizeof (*footprint_region) +
			 roundup((footprint_region->cfr_num_pages -
				  footprint_header->cf_last_zeroes),
				 sizeof (int)) -
			 (footprint_region->cfr_num_pages -
			  footprint_header->cf_last_zeroes));
//		printf("FBDP %s:%d region 0x%x 0x%llx 0x%x vme_start 0x%llx pages_delta 0x%llx region_delta 0x%x\n", __FUNCTION__, __LINE__, footprint_header->cf_last_region, footprint_region->cfr_vaddr, footprint_region->cfr_num_pages, old_entry->vme_start, num_pages_delta, region_offset_delta);
		if (region_offset_delta < num_pages_delta ||
		    os_add3_overflow(footprint_region->cfr_num_pages,
				     (uint32_t) num_pages_delta,
				     1,
				     &num_pages_tmp)) {
			/*
			 * Storing data for this gap would take more space
			 * than inserting a new footprint region header:
			 * let's start a new region and save space. If it's a
			 * tie, let's avoid using a new region, since that
			 * would require more region hops to find the right
			 * range during lookups.
			 *
			 * If the current region's cfr_num_pages would overflow
			 * if we added "zero" page dispositions for the gap,
			 * no choice but to start a new region.
			 */
//			printf("FBDP %s:%d new region\n", __FUNCTION__, __LINE__);
			new_footprint_region =
				vm_map_corpse_footprint_new_region(footprint_header);
			/* check that we're not going over the edge */
			if (new_footprint_region == NULL) {
				goto over_the_edge;
			}
			footprint_region = new_footprint_region;
			/* initialize new region as empty */
			footprint_region->cfr_vaddr = old_entry->vme_start;
			footprint_region->cfr_num_pages = 0;
		} else {
			/*
			 * Store "zero" page dispositions for the missing
			 * pages.
			 */
//			printf("FBDP %s:%d zero gap\n", __FUNCTION__, __LINE__);
			for (; num_pages_delta > 0; num_pages_delta--) {
				next_disp_p =
					((unsigned char *) footprint_region +
					 sizeof (*footprint_region) +
					 footprint_region->cfr_num_pages);
				/* check that we're not going over the edge */
				if ((uintptr_t)next_disp_p >= footprint_edge) {
					goto over_the_edge;
				}
				/* store "zero" disposition for this gap page */
				footprint_region->cfr_num_pages++;
				*next_disp_p = (unsigned char) 0;
				footprint_header->cf_last_zeroes++;
			}
		}
	}

	for (va = old_entry->vme_start;
	     va < old_entry->vme_end;
	     va += PAGE_SIZE) {
		vm_object_t	object;

		object = VME_OBJECT(old_entry);
		if (!old_entry->is_sub_map &&
		    old_entry->iokit_acct &&
		    object != VM_OBJECT_NULL &&
		    object->internal &&
		    object->purgable == VM_PURGABLE_DENY) {
			/*
			 * Non-purgeable IOKit memory: phys_footprint
			 * includes the entire virtual mapping.
			 * Since the forked corpse's VM map entry will not
			 * have "iokit_acct", pretend that this page's
			 * disposition is "present & internal", so that it
			 * shows up in the forked corpse's footprint.
			 */
			disp = (PMAP_QUERY_PAGE_PRESENT |
				PMAP_QUERY_PAGE_INTERNAL);
		} else {
			disp = 0;
			pmap_query_page_info(old_map->pmap,
					     va,
					     &disp);
		}

//		if (va < SHARED_REGION_BASE_ARM64) printf("FBDP collect map %p va 0x%llx disp 0x%x\n", new_map, va, disp);

		if (disp == 0 && footprint_region->cfr_num_pages == 0) {
			/*
			 * Ignore "zero" dispositions at start of
			 * region: just move start of region.
			 */
			footprint_region->cfr_vaddr += PAGE_SIZE;
			continue;
		}

		/* would region's cfr_num_pages overflow? */
		if (os_add_overflow(footprint_region->cfr_num_pages, 1,
				    &num_pages_tmp)) {
			/* overflow: create a new region */
			new_footprint_region =
				vm_map_corpse_footprint_new_region(
					footprint_header);
			if (new_footprint_region == NULL) {
				goto over_the_edge;
			}
			footprint_region = new_footprint_region;
			footprint_region->cfr_vaddr = va;
			footprint_region->cfr_num_pages = 0;
		}

		next_disp_p = ((unsigned char *)footprint_region +
			       sizeof (*footprint_region) +
			       footprint_region->cfr_num_pages);
		/* check that we're not going over the edge */
		if ((uintptr_t)next_disp_p >= footprint_edge) {
			goto over_the_edge;
		}
		/* store this dispostion */
		*next_disp_p = (unsigned char) disp;
		footprint_region->cfr_num_pages++;

		if (disp != 0) {
			/* non-zero disp: break the current zero streak */
			footprint_header->cf_last_zeroes = 0;
			/* done */
			continue;
		}

		/* zero disp: add to the current streak of zeroes */
		footprint_header->cf_last_zeroes++;
		if ((footprint_header->cf_last_zeroes +
		     roundup((footprint_region->cfr_num_pages -
			      footprint_header->cf_last_zeroes) &
			     (sizeof (int) - 1),
			     sizeof (int))) <
		    (sizeof (*footprint_header))) {
			/*
			 * There are not enough trailing "zero" dispositions
			 * (+ the extra padding we would need for the previous
			 * region); creating a new region would not save space
			 * at this point, so let's keep this "zero" disposition
			 * in this region and reconsider later.
			 */
			continue;
		}
		/*
		 * Create a new region to avoid having too many consecutive
		 * "zero" dispositions.
		 */
		new_footprint_region =
			vm_map_corpse_footprint_new_region(footprint_header);
		if (new_footprint_region == NULL) {
			goto over_the_edge;
		}
		footprint_region = new_footprint_region;
		/* initialize the new region as empty ... */
		footprint_region->cfr_num_pages = 0;
		/* ... and skip this "zero" disp */
		footprint_region->cfr_vaddr = va + PAGE_SIZE;
	}

	return KERN_SUCCESS;

over_the_edge:
//	printf("FBDP map %p footprint was full for va 0x%llx\n", new_map, va);
	vm_map_corpse_footprint_full++;
	return KERN_RESOURCE_SHORTAGE;
}