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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 unsigned long* ptelist ; 
 int /*<<< orphan*/  sun3_put_pte (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  virt_to_pfn (unsigned long) ; 

__attribute__((used)) static unsigned long dvma_page(unsigned long kaddr, unsigned long vaddr)
{
	unsigned long pte;
	unsigned long j;
	pte_t ptep;

	j = *(volatile unsigned long *)kaddr;
	*(volatile unsigned long *)kaddr = j;

	ptep = pfn_pte(virt_to_pfn(kaddr), PAGE_KERNEL);
	pte = pte_val(ptep);
//		printk("dvma_remap: addr %lx -> %lx pte %08lx len %x\n",
//		       kaddr, vaddr, pte, len);
	if(ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] != pte) {
		sun3_put_pte(vaddr, pte);
		ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] = pte;
	}

	return (vaddr + (kaddr & ~PAGE_MASK));

}