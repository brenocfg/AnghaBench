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
 int /*<<< orphan*/  BARRIER () ; 
 unsigned long CKSEG0 ; 
 unsigned long long PAGE_MASK ; 
 int /*<<< orphan*/  msk2str (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long read_c0_entryhi () ; 
 unsigned long long read_c0_entrylo0 () ; 
 unsigned long long read_c0_entrylo1 () ; 
 unsigned int read_c0_index () ; 
 unsigned int read_c0_pagemask () ; 
 int /*<<< orphan*/  tlb_read () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_index (unsigned int) ; 

__attribute__((used)) static void dump_tlb(int first, int last)
{
	unsigned long s_entryhi, entryhi, asid;
	unsigned long long entrylo0, entrylo1;
	unsigned int s_index, pagemask, c0, c1, i;

	s_entryhi = read_c0_entryhi();
	s_index = read_c0_index();
	asid = s_entryhi & 0xff;

	for (i = first; i <= last; i++) {
		write_c0_index(i);
		BARRIER();
		tlb_read();
		BARRIER();
		pagemask = read_c0_pagemask();
		entryhi  = read_c0_entryhi();
		entrylo0 = read_c0_entrylo0();
		entrylo1 = read_c0_entrylo1();

		/* Unused entries have a virtual address of CKSEG0.  */
		if ((entryhi & ~0x1ffffUL) != CKSEG0
		    && (entryhi & 0xff) == asid) {
#ifdef CONFIG_32BIT
			int width = 8;
#else
			int width = 11;
#endif
			/*
			 * Only print entries in use
			 */
			printk("Index: %2d pgmask=%s ", i, msk2str(pagemask));

			c0 = (entrylo0 >> 3) & 7;
			c1 = (entrylo1 >> 3) & 7;

			printk("va=%0*lx asid=%02lx\n",
			       width, (entryhi & ~0x1fffUL),
			       entryhi & 0xff);
			printk("\t[pa=%0*llx c=%d d=%d v=%d g=%d] ",
			       width,
			       (entrylo0 << 6) & PAGE_MASK, c0,
			       (entrylo0 & 4) ? 1 : 0,
			       (entrylo0 & 2) ? 1 : 0,
			       (entrylo0 & 1) ? 1 : 0);
			printk("[pa=%0*llx c=%d d=%d v=%d g=%d]\n",
			       width,
			       (entrylo1 << 6) & PAGE_MASK, c1,
			       (entrylo1 & 4) ? 1 : 0,
			       (entrylo1 & 2) ? 1 : 0,
			       (entrylo1 & 1) ? 1 : 0);
		}
	}
	printk("\n");

	write_c0_entryhi(s_entryhi);
	write_c0_index(s_index);
}