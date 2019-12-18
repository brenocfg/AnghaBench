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
 int /*<<< orphan*/  printk (char*,...) ; 
 int read_c0_entryhi () ; 
 unsigned long read_c0_entrylo0 () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned int) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 

__attribute__((used)) static void dump_tlb(int first, int last)
{
	int	i;
	unsigned int asid;
	unsigned long entryhi, entrylo0;

	asid = read_c0_entryhi() & 0xfc0;

	for (i = first; i <= last; i++) {
		write_c0_index(i<<8);
		__asm__ __volatile__(
			".set\tnoreorder\n\t"
			"tlbr\n\t"
			"nop\n\t"
			".set\treorder");
		entryhi  = read_c0_entryhi();
		entrylo0 = read_c0_entrylo0();

		/* Unused entries have a virtual address of KSEG0.  */
		if ((entryhi & 0xffffe000) != 0x80000000
		    && (entryhi & 0xfc0) == asid) {
			/*
			 * Only print entries in use
			 */
			printk("Index: %2d ", i);

			printk("va=%08lx asid=%08lx"
			       "  [pa=%06lx n=%d d=%d v=%d g=%d]",
			       (entryhi & 0xffffe000),
			       entryhi & 0xfc0,
			       entrylo0 & PAGE_MASK,
			       (entrylo0 & (1 << 11)) ? 1 : 0,
			       (entrylo0 & (1 << 10)) ? 1 : 0,
			       (entrylo0 & (1 << 9)) ? 1 : 0,
			       (entrylo0 & (1 << 8)) ? 1 : 0);
		}
	}
	printk("\n");

	write_c0_entryhi(asid);
}