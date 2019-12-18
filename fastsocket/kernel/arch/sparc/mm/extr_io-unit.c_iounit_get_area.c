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
struct iounit_struct {unsigned long* rotor; unsigned long* limit; int /*<<< orphan*/ * page_table; int /*<<< orphan*/  bmap; } ;
typedef  int /*<<< orphan*/  iopte_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOD (char*) ; 
 unsigned long IOUNIT_DMA_BASE ; 
 int /*<<< orphan*/  MKIOPTE (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __iopte (scalar_t__) ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ iopte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned long,int) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long iounit_get_area(struct iounit_struct *iounit, unsigned long vaddr, int size)
{
	int i, j, k, npages;
	unsigned long rotor, scan, limit;
	iopte_t iopte;

        npages = ((vaddr & ~PAGE_MASK) + size + (PAGE_SIZE-1)) >> PAGE_SHIFT;

	/* A tiny bit of magic ingredience :) */
	switch (npages) {
	case 1: i = 0x0231; break;
	case 2: i = 0x0132; break;
	default: i = 0x0213; break;
	}
	
	IOD(("iounit_get_area(%08lx,%d[%d])=", vaddr, size, npages));
	
next:	j = (i & 15);
	rotor = iounit->rotor[j - 1];
	limit = iounit->limit[j];
	scan = rotor;
nexti:	scan = find_next_zero_bit(iounit->bmap, limit, scan);
	if (scan + npages > limit) {
		if (limit != rotor) {
			limit = rotor;
			scan = iounit->limit[j - 1];
			goto nexti;
		}
		i >>= 4;
		if (!(i & 15))
			panic("iounit_get_area: Couldn't find free iopte slots for (%08lx,%d)\n", vaddr, size);
		goto next;
	}
	for (k = 1, scan++; k < npages; k++)
		if (test_bit(scan++, iounit->bmap))
			goto nexti;
	iounit->rotor[j - 1] = (scan < limit) ? scan : iounit->limit[j - 1];
	scan -= npages;
	iopte = MKIOPTE(__pa(vaddr & PAGE_MASK));
	vaddr = IOUNIT_DMA_BASE + (scan << PAGE_SHIFT) + (vaddr & ~PAGE_MASK);
	for (k = 0; k < npages; k++, iopte = __iopte(iopte_val(iopte) + 0x100), scan++) {
		set_bit(scan, iounit->bmap);
		iounit->page_table[scan] = iopte;
	}
	IOD(("%08lx\n", vaddr));
	return vaddr;
}