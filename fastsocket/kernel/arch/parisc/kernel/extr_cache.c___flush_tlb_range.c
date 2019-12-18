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
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  mtsp (unsigned long,int) ; 
 int /*<<< orphan*/  pdtlb (unsigned long) ; 
 int /*<<< orphan*/  pitlb (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 
 scalar_t__ split_tlb ; 

void __flush_tlb_range(unsigned long sid, unsigned long start,
		       unsigned long end)
{
	unsigned long npages;

	npages = ((end - (start & PAGE_MASK)) + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (npages >= 512)  /* 2MB of space: arbitrary, should be tuned */
		flush_tlb_all();
	else {
		unsigned long flags;

		mtsp(sid, 1);
		purge_tlb_start(flags);
		if (split_tlb) {
			while (npages--) {
				pdtlb(start);
				pitlb(start);
				start += PAGE_SIZE;
			}
		} else {
			while (npages--) {
				pdtlb(start);
				start += PAGE_SIZE;
			}
		}
		purge_tlb_end(flags);
	}
}