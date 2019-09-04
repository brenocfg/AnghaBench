#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int vm_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ppnum_t ;
typedef  int addr64_t ;
struct TYPE_5__ {scalar_t__ resident_count; scalar_t__ resident_max; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ IS_MANAGED_PAGE (int) ; 
 int PAGE_SIZE ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* kernel_pmap ; 
 int pmap_find_phys (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_remove (TYPE_2__*,int,int) ; 
 int pmap_valid_page (int) ; 
 int round_page_64 (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_create (int,int) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_wire_count ; 
 int /*<<< orphan*/  vm_page_wire_count_initial ; 

void
ml_static_mfree(
	vm_offset_t vaddr,
	vm_size_t size)
{
	addr64_t vaddr_cur;
	ppnum_t ppn;
	uint32_t freed_pages = 0;
	assert(vaddr >= VM_MIN_KERNEL_ADDRESS);

	assert((vaddr & (PAGE_SIZE-1)) == 0); /* must be page aligned */

	for (vaddr_cur = vaddr;
 	     vaddr_cur < round_page_64(vaddr+size);
	     vaddr_cur += PAGE_SIZE) {
		ppn = pmap_find_phys(kernel_pmap, vaddr_cur);
		if (ppn != (vm_offset_t)NULL) {
		        kernel_pmap->stats.resident_count++;
			if (kernel_pmap->stats.resident_count >
			    kernel_pmap->stats.resident_max) {
				kernel_pmap->stats.resident_max =
					kernel_pmap->stats.resident_count;
			}
			pmap_remove(kernel_pmap, vaddr_cur, vaddr_cur+PAGE_SIZE);
			assert(pmap_valid_page(ppn));
			if (IS_MANAGED_PAGE(ppn)) {
				vm_page_create(ppn,(ppn+1));
				freed_pages++;
			}
		}
	}
	vm_page_lockspin_queues();
	vm_page_wire_count -= freed_pages;
	vm_page_wire_count_initial -= freed_pages;
	vm_page_unlock_queues();

#if	DEBUG	
	kprintf("ml_static_mfree: Released 0x%x pages at VA %p, size:0x%llx, last ppn: 0x%x\n", freed_pages, (void *)vaddr, (uint64_t)size, ppn);
#endif
}