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
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

void clear_user_page_asm(void *page, unsigned long vaddr)
{
	unsigned long flags;
	/* This function is implemented in assembly in pacache.S */
	extern void __clear_user_page_asm(void *page, unsigned long vaddr);

	purge_tlb_start(flags);
	__clear_user_page_asm(page, vaddr);
	purge_tlb_end(flags);
}