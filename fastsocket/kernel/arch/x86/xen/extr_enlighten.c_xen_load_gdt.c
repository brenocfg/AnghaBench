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
struct desc_struct {int dummy; } ;
struct desc_ptr {unsigned long address; int size; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 scalar_t__ HYPERVISOR_set_gdt (unsigned long*,unsigned int) ; 
 unsigned long PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 void* __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,int*) ; 
 int /*<<< orphan*/  make_lowmem_page_readonly (void*) ; 
 unsigned long pfn_to_mfn (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_load_gdt(const struct desc_ptr *dtr)
{
	unsigned long va = dtr->address;
	unsigned int size = dtr->size + 1;
	unsigned pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	unsigned long frames[pages];
	int f;

	/*
	 * A GDT can be up to 64k in size, which corresponds to 8192
	 * 8-byte entries, or 16 4k pages..
	 */

	BUG_ON(size > 65536);
	BUG_ON(va & ~PAGE_MASK);

	for (f = 0; va < dtr->address + size; va += PAGE_SIZE, f++) {
		int level;
		pte_t *ptep;
		unsigned long pfn, mfn;
		void *virt;

		/*
		 * The GDT is per-cpu and is in the percpu data area.
		 * That can be virtually mapped, so we need to do a
		 * page-walk to get the underlying MFN for the
		 * hypercall.  The page can also be in the kernel's
		 * linear range, so we need to RO that mapping too.
		 */
		ptep = lookup_address(va, &level);
		BUG_ON(ptep == NULL);

		pfn = pte_pfn(*ptep);
		mfn = pfn_to_mfn(pfn);
		virt = __va(PFN_PHYS(pfn));

		frames[f] = mfn;

		make_lowmem_page_readonly((void *)va);
		make_lowmem_page_readonly(virt);
	}

	if (HYPERVISOR_set_gdt(frames, size / sizeof(struct desc_struct)))
		BUG();
}