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

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_OFFSET ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SUN4C_PAGE_KERNEL ; 
 unsigned long SUN4C_REAL_PGDIR_ALIGN (unsigned long) ; 
 scalar_t__ SUN4C_REAL_PGDIR_SIZE ; 
 unsigned long _SUN4C_PAGE_NOCACHE ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_locked_segment (unsigned long) ; 
 unsigned long iobuffer_map_size ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4c_flush_page (unsigned long) ; 
 unsigned long sun4c_iobuffer_high ; 
 int /*<<< orphan*/  sun4c_iobuffer_map ; 
 unsigned long sun4c_iobuffer_start ; 
 int /*<<< orphan*/  sun4c_put_pte (unsigned long,unsigned long) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *sun4c_lockarea(char *vaddr, unsigned long size)
{
	unsigned long base, scan;
	unsigned long npages;
	unsigned long vpage;
	unsigned long pte;
	unsigned long apage;
	unsigned long high;
	unsigned long flags;

	npages = (((unsigned long)vaddr & ~PAGE_MASK) +
		  size + (PAGE_SIZE-1)) >> PAGE_SHIFT;

	scan = 0;
	local_irq_save(flags);
	for (;;) {
		scan = find_next_zero_bit(sun4c_iobuffer_map,
					  iobuffer_map_size, scan);
		if ((base = scan) + npages > iobuffer_map_size) goto abend;
		for (;;) {
			if (scan >= base + npages) goto found;
			if (test_bit(scan, sun4c_iobuffer_map)) break;
			scan++;
		}
	}

found:
	high = ((base + npages) << PAGE_SHIFT) + sun4c_iobuffer_start;
	high = SUN4C_REAL_PGDIR_ALIGN(high);
	while (high > sun4c_iobuffer_high) {
		get_locked_segment(sun4c_iobuffer_high);
		sun4c_iobuffer_high += SUN4C_REAL_PGDIR_SIZE;
	}

	vpage = ((unsigned long) vaddr) & PAGE_MASK;
	for (scan = base; scan < base+npages; scan++) {
		pte = ((vpage-PAGE_OFFSET) >> PAGE_SHIFT);
 		pte |= pgprot_val(SUN4C_PAGE_KERNEL);
		pte |= _SUN4C_PAGE_NOCACHE;
		set_bit(scan, sun4c_iobuffer_map);
		apage = (scan << PAGE_SHIFT) + sun4c_iobuffer_start;

		/* Flush original mapping so we see the right things later. */
		sun4c_flush_page(vpage);

		sun4c_put_pte(apage, pte);
		vpage += PAGE_SIZE;
	}
	local_irq_restore(flags);
	return (char *) ((base << PAGE_SHIFT) + sun4c_iobuffer_start +
			 (((unsigned long) vaddr) & ~PAGE_MASK));

abend:
	local_irq_restore(flags);
	printk("DMA vaddr=0x%p size=%08lx\n", vaddr, size);
	panic("Out of iobuffer table");
	return NULL;
}