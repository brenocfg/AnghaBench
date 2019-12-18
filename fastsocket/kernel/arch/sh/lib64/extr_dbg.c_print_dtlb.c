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
 unsigned long DTLB_BASE ; 
 char* HOW_TO_READ_TLB_CONTENT ; 
 int MAX_TLBs ; 
 scalar_t__ TLB_STEP ; 
 int /*<<< orphan*/  print_single_tlb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

void print_dtlb(void)
{
	int count;
	unsigned long tlb;

	printk(" ================= SH-5 D-TLBs Status ===================\n");
	printk(HOW_TO_READ_TLB_CONTENT);
	tlb = DTLB_BASE;
	for (count = 0; count < MAX_TLBs; count++, tlb += TLB_STEP)
		print_single_tlb(tlb, 0);
	printk
	    (" =============================================================\n");
}