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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_user_page_asm (void*,unsigned long) ; 
 int /*<<< orphan*/  pdtlb_kernel (void*) ; 
 int /*<<< orphan*/  purge_kernel_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

void clear_user_page(void *page, unsigned long vaddr, struct page *pg)
{
	unsigned long flags;

	purge_kernel_dcache_page((unsigned long)page);
	purge_tlb_start(flags);
	pdtlb_kernel(page);
	purge_tlb_end(flags);
	clear_user_page_asm(page, vaddr);
}