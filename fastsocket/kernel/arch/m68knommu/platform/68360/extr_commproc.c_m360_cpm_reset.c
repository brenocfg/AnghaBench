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
struct quicc {int cp_cr; int sdma_sdcr; } ;

/* Variables and functions */
 int CMD_FLAG ; 
 scalar_t__ CPM_DATAONLY_BASE ; 
 scalar_t__ CPM_DATAONLY_SIZE ; 
 int SOFTWARE_RESET ; 
 scalar_t__ _quicc_base ; 
 scalar_t__ dp_alloc_base ; 
 scalar_t__ dp_alloc_top ; 
 struct quicc* pquicc ; 

void m360_cpm_reset()
{
/* 	pte_t		   *pte; */

	pquicc = (struct quicc *)(_quicc_base); /* initialized in crt0_rXm.S */

	/* Perform a CPM reset. */
	pquicc->cp_cr = (SOFTWARE_RESET | CMD_FLAG);

	/* Wait for CPM to become ready (should be 2 clocks). */
	while (pquicc->cp_cr & CMD_FLAG);

	/* On the recommendation of the 68360 manual, p. 7-60
	 * - Set sdma interrupt service mask to 7
	 * - Set sdma arbitration ID to 4
	 */
	pquicc->sdma_sdcr = 0x0740;


	/* Claim the DP memory for our use.
	 */
	dp_alloc_base = CPM_DATAONLY_BASE;
	dp_alloc_top = dp_alloc_base + CPM_DATAONLY_SIZE;


	/* Set the host page for allocation.
	 */
	/* 	host_buffer = host_page_addr; */
	/* 	host_end = host_page_addr + PAGE_SIZE; */

	/* 	pte = find_pte(&init_mm, host_page_addr); */
	/* 	pte_val(*pte) |= _PAGE_NO_CACHE; */
	/* 	flush_tlb_page(current->mm->mmap, host_buffer); */
	
	/* Tell everyone where the comm processor resides.
	*/
/* 	cpmp = (cpm360_t *)commproc; */
}