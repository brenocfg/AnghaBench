#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int shift; } ;
struct TYPE_3__ {int (* hpte_insert ) (unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG (char*,unsigned long,unsigned long,unsigned long,unsigned long,int,int) ; 
 unsigned long HPTES_PER_GROUP ; 
 unsigned long HPTE_R_N ; 
 int /*<<< orphan*/  HPTE_V_BOLTED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_hash (unsigned long,unsigned int,int) ; 
 unsigned long hpt_va (unsigned long,unsigned long,int) ; 
 unsigned long htab_convert_pte_flags (unsigned long) ; 
 unsigned long htab_hash_mask ; 
 unsigned long linear_map_hash_count ; 
 int* linear_map_hash_slots ; 
 TYPE_2__* mmu_psize_defs ; 
 scalar_t__ overlaps_kernel_text (unsigned long,unsigned long) ; 
 TYPE_1__ ppc_md ; 
 int stub1 (unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ; 

int htab_bolt_mapping(unsigned long vstart, unsigned long vend,
		      unsigned long pstart, unsigned long prot,
		      int psize, int ssize)
{
	unsigned long vaddr, paddr;
	unsigned int step, shift;
	int ret = 0;

	shift = mmu_psize_defs[psize].shift;
	step = 1 << shift;

	prot = htab_convert_pte_flags(prot);

	DBG("htab_bolt_mapping(%lx..%lx -> %lx (%lx,%d,%d)\n",
	    vstart, vend, pstart, prot, psize, ssize);

	for (vaddr = vstart, paddr = pstart; vaddr < vend;
	     vaddr += step, paddr += step) {
		unsigned long hash, hpteg;
		unsigned long vsid = get_kernel_vsid(vaddr, ssize);
		unsigned long va = hpt_va(vaddr, vsid, ssize);
		unsigned long tprot = prot;

		/* Make kernel text executable */
		if (overlaps_kernel_text(vaddr, vaddr + step))
			tprot &= ~HPTE_R_N;

		hash = hpt_hash(va, shift, ssize);
		hpteg = ((hash & htab_hash_mask) * HPTES_PER_GROUP);

		BUG_ON(!ppc_md.hpte_insert);
		ret = ppc_md.hpte_insert(hpteg, va, paddr, tprot,
					 HPTE_V_BOLTED, psize, ssize);

		if (ret < 0)
			break;
#ifdef CONFIG_DEBUG_PAGEALLOC
		if ((paddr >> PAGE_SHIFT) < linear_map_hash_count)
			linear_map_hash_slots[paddr >> PAGE_SHIFT] = ret | 0x80;
#endif /* CONFIG_DEBUG_PAGEALLOC */
	}
	return ret < 0 ? ret : 0;
}