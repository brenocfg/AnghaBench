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
struct TYPE_2__ {unsigned long current_pages; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  GFP_BALLOON ; 
 int HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 int HYPERVISOR_update_va_mapping (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_P2M_ENTRY ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  XENMEM_decrease_reservation ; 
 int /*<<< orphan*/  __pte_ma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_phys_to_machine (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ __va (unsigned long) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balloon_append (int /*<<< orphan*/ ) ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/ * frame_list ; 
 int /*<<< orphan*/  kmap_flush_unused () ; 
 unsigned long mfn_to_pfn (int /*<<< orphan*/ ) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_to_mfn (unsigned long) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  scrub_page (struct page*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decrease_reservation(unsigned long nr_pages)
{
	unsigned long  pfn, i;
	struct page   *page;
	int            need_sleep = 0;
	int ret;
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = 0,
		.domid        = DOMID_SELF
	};

	if (nr_pages > ARRAY_SIZE(frame_list))
		nr_pages = ARRAY_SIZE(frame_list);

	for (i = 0; i < nr_pages; i++) {
		if ((page = alloc_page(GFP_BALLOON)) == NULL) {
			nr_pages = i;
			need_sleep = 1;
			break;
		}

		pfn = page_to_pfn(page);
		frame_list[i] = pfn_to_mfn(pfn);

		scrub_page(page);

		if (!PageHighMem(page)) {
			ret = HYPERVISOR_update_va_mapping(
				(unsigned long)__va(pfn << PAGE_SHIFT),
				__pte_ma(0), 0);
			BUG_ON(ret);
                }

	}

	/* Ensure that ballooned highmem pages don't have kmaps. */
	kmap_flush_unused();
	flush_tlb_all();

	/* No more mappings: invalidate P2M and add to balloon. */
	for (i = 0; i < nr_pages; i++) {
		pfn = mfn_to_pfn(frame_list[i]);
		__set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
		balloon_append(pfn_to_page(pfn));
	}

	set_xen_guest_handle(reservation.extent_start, frame_list);
	reservation.nr_extents   = nr_pages;
	ret = HYPERVISOR_memory_op(XENMEM_decrease_reservation, &reservation);
	BUG_ON(ret != nr_pages);

	balloon_stats.current_pages -= nr_pages;

	return need_sleep;
}