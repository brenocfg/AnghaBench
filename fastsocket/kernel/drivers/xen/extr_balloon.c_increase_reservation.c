#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xen_memory_reservation {unsigned long nr_extents; int /*<<< orphan*/  extent_start; int /*<<< orphan*/  domid; int /*<<< orphan*/  extent_order; int /*<<< orphan*/  address_bits; } ;
struct page {int dummy; } ;
struct TYPE_2__ {long current_pages; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 long HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 int HYPERVISOR_update_va_mapping (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int /*<<< orphan*/  XENMEM_populate_physmap ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ __va (unsigned long) ; 
 struct page* balloon_first_page () ; 
 struct page* balloon_next_page (struct page*) ; 
 struct page* balloon_retrieve () ; 
 TYPE_1__ balloon_stats ; 
 void** frame_list ; 
 int /*<<< orphan*/  init_page_count (struct page*) ; 
 int /*<<< orphan*/  mfn_pte (void*,int /*<<< orphan*/ ) ; 
 void* page_to_pfn (struct page*) ; 
 scalar_t__ phys_to_machine_mapping_valid (unsigned long) ; 
 int /*<<< orphan*/  set_phys_to_machine (unsigned long,void*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  xen_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int increase_reservation(unsigned long nr_pages)
{
	unsigned long  pfn, i;
	struct page   *page;
	long           rc;
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = 0,
		.domid        = DOMID_SELF
	};

	if (nr_pages > ARRAY_SIZE(frame_list))
		nr_pages = ARRAY_SIZE(frame_list);

	page = balloon_first_page();
	for (i = 0; i < nr_pages; i++) {
		BUG_ON(page == NULL);
		frame_list[i] = page_to_pfn(page);
		page = balloon_next_page(page);
	}

	set_xen_guest_handle(reservation.extent_start, frame_list);
	reservation.nr_extents = nr_pages;
	rc = HYPERVISOR_memory_op(XENMEM_populate_physmap, &reservation);
	if (rc < 0)
		goto out;

	for (i = 0; i < rc; i++) {
		page = balloon_retrieve();
		BUG_ON(page == NULL);

		pfn = page_to_pfn(page);
		BUG_ON(!xen_feature(XENFEAT_auto_translated_physmap) &&
		       phys_to_machine_mapping_valid(pfn));

		set_phys_to_machine(pfn, frame_list[i]);

		/* Link back into the page tables if not highmem. */
		if (!PageHighMem(page)) {
			int ret;
			ret = HYPERVISOR_update_va_mapping(
				(unsigned long)__va(pfn << PAGE_SHIFT),
				mfn_pte(frame_list[i], PAGE_KERNEL),
				0);
			BUG_ON(ret);
		}

		/* Relinquish the page back to the allocator. */
		ClearPageReserved(page);
		init_page_count(page);
		__free_page(page);
	}

	balloon_stats.current_pages += rc;

 out:
	return rc < 0 ? rc : rc != nr_pages;
}