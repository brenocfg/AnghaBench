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
 unsigned char CONTEXTS_NUM ; 
 int PAGE_OFFSET ; 
 unsigned char SUN3_INVALID_PMEG ; 
 int /*<<< orphan*/  SUN3_PAGE_SYSTEM ; 
 int SUN3_PMEG_MASK ; 
 int SUN3_PMEG_SIZE ; 
 scalar_t__ SUN3_PTE_SIZE ; 
 int* pmeg_alloc ; 
 int* pmeg_ctx ; 
 int* pmeg_vaddr ; 
 int /*<<< orphan*/  printk (char*,unsigned char,int,int) ; 
 int /*<<< orphan*/  sun3_put_context (int) ; 
 int /*<<< orphan*/  sun3_put_pte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun3_put_segmap (int,unsigned char) ; 

inline void mmu_emu_map_pmeg (int context, int vaddr)
{
	static unsigned char curr_pmeg = 128;
	int i;

	/* Round address to PMEG boundary. */
	vaddr &= ~SUN3_PMEG_MASK;

	/* Find a spare one. */
	while (pmeg_alloc[curr_pmeg] == 2)
		++curr_pmeg;


#ifdef DEBUG_MMU_EMU
printk("mmu_emu_map_pmeg: pmeg %x to context %d vaddr %x\n",
       curr_pmeg, context, vaddr);
#endif

	/* Invalidate old mapping for the pmeg, if any */
	if (pmeg_alloc[curr_pmeg] == 1) {
		sun3_put_context(pmeg_ctx[curr_pmeg]);
		sun3_put_segmap (pmeg_vaddr[curr_pmeg], SUN3_INVALID_PMEG);
		sun3_put_context(context);
	}

	/* Update PMEG management structures. */
	// don't take pmeg's away from the kernel...
	if(vaddr >= PAGE_OFFSET) {
		/* map kernel pmegs into all contexts */
		unsigned char i;

		for(i = 0; i < CONTEXTS_NUM; i++) {
			sun3_put_context(i);
			sun3_put_segmap (vaddr, curr_pmeg);
		}
		sun3_put_context(context);
		pmeg_alloc[curr_pmeg] = 2;
		pmeg_ctx[curr_pmeg] = 0;

	}
	else {
		pmeg_alloc[curr_pmeg] = 1;
		pmeg_ctx[curr_pmeg] = context;
		sun3_put_segmap (vaddr, curr_pmeg);

	}
	pmeg_vaddr[curr_pmeg] = vaddr;

	/* Set hardware mapping and clear the old PTE entries. */
	for (i=0; i<SUN3_PMEG_SIZE; i+=SUN3_PTE_SIZE)
		sun3_put_pte (vaddr + i, SUN3_PAGE_SYSTEM);

	/* Consider a different one next time. */
	++curr_pmeg;
}