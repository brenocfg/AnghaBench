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
typedef  int /*<<< orphan*/  regType_t ;

/* Variables and functions */
 unsigned int GET_ASID (int /*<<< orphan*/ ) ; 
 unsigned int GET_CBEHAVIOR (int /*<<< orphan*/ ) ; 
 unsigned int GET_EPN (int /*<<< orphan*/ ) ; 
 char* GET_PAGE_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int GET_PPN (int /*<<< orphan*/ ) ; 
 char* GET_PROTECTION (int /*<<< orphan*/ ) ; 
 unsigned int GET_SHARED (int /*<<< orphan*/ ) ; 
 unsigned int GET_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOW_TO_READ_TLB_CONTENT ; 
 unsigned long TLB_STEP ; 
 int /*<<< orphan*/  getConfigReg (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void print_single_tlb(unsigned long tlb, int single_print)
{
	regType_t pteH;
	regType_t pteL;
	unsigned int valid, shared, asid, epn, cb, ppn;
	char *pSize;
	char *pProt;

	/*
	   ** in case of single print <single_print> is true, this implies:
	   **   1) print the TLB in any case also if NOT VALID
	   **   2) print out the header
	 */

	pteH = getConfigReg(tlb);
	valid = GET_VALID(pteH);
	if (single_print)
		printk(HOW_TO_READ_TLB_CONTENT);
	else if (!valid)
		return;

	pteL = getConfigReg(tlb + 1);

	shared = GET_SHARED(pteH);
	asid = GET_ASID(pteH);
	epn = GET_EPN(pteH);
	cb = GET_CBEHAVIOR(pteL);
	pSize = GET_PAGE_SIZE(pteL);
	pProt = GET_PROTECTION(pteL);
	ppn = GET_PPN(pteL);
	printk("[%c%2ld]  0x%08x  0x%08x  %03d   %02x    %02x   %4s    %s\n",
	       ((valid) ? ' ' : 'u'), ((tlb & 0x0ffff) / TLB_STEP),
	       ppn, epn, asid, shared, cb, pSize, pProt);
}