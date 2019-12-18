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
struct xen_memory_reservation {int nr_extents; int /*<<< orphan*/  extent_start; int /*<<< orphan*/  domid; int /*<<< orphan*/  extent_order; int /*<<< orphan*/  address_bits; } ;
struct vm_struct {scalar_t__ addr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 unsigned long HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  XENMEM_populate_physmap ; 
 unsigned long __pa (scalar_t__) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 unsigned int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vm_struct*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,unsigned long*) ; 

void xen_free_vm_area(struct vm_struct *area)
{
	unsigned int order = get_order(area->size);
	unsigned long i;
	unsigned long phys_addr = __pa(area->addr);

	/* This area is used for foreign page mappping.
	 * So underlying machine page may not be assigned. */
	for (i = 0; i < (1 << order); i++) {
		unsigned long ret;
		unsigned long gpfn = (phys_addr >> PAGE_SHIFT) + i;
		struct xen_memory_reservation reservation = {
			.nr_extents   = 1,
			.address_bits = 0,
			.extent_order = 0,
			.domid        = DOMID_SELF
		};
		set_xen_guest_handle(reservation.extent_start, &gpfn);
		ret = HYPERVISOR_memory_op(XENMEM_populate_physmap,
					   &reservation);
		BUG_ON(ret != 1);
	}
	free_pages((unsigned long)area->addr, order);
	kfree(area);
}