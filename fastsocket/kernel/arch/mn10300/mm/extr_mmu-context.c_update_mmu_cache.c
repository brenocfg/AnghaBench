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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int DPTEL ; 
 unsigned long DPTEU ; 
 int IPTEL ; 
 unsigned long IPTEU ; 
 unsigned long MMU_NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 unsigned long _PAGE_NX ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long mm_context (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 unsigned long xPTEL_UNUSED1 ; 
 unsigned long xPTEL_UNUSED2 ; 
 int xPTEL_V ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t pte)
{
	unsigned long pteu, ptel, cnx, flags;

	addr &= PAGE_MASK;
	ptel = pte_val(pte) & ~(xPTEL_UNUSED1 | xPTEL_UNUSED2);

	/* make sure the context doesn't migrate and defend against
	 * interference from vmalloc'd regions */
	local_irq_save(flags);

	cnx = mm_context(vma->vm_mm);

	if (cnx != MMU_NO_CONTEXT) {
		pteu = addr | (cnx & 0x000000ffUL);
		if (!(pte_val(pte) & _PAGE_NX)) {
			IPTEU = pteu;
			if (IPTEL & xPTEL_V)
				IPTEL = ptel;
		}
		DPTEU = pteu;
		if (DPTEL & xPTEL_V)
			DPTEL = ptel;
	}

	local_irq_restore(flags);
}