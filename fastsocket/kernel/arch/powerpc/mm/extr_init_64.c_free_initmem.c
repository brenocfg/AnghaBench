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
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  POISON_FREE_INITMEM ; 
 scalar_t__ __init_begin ; 
 scalar_t__ __init_end ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 int /*<<< orphan*/  totalram_pages ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void free_initmem(void)
{
	unsigned long addr;

	addr = (unsigned long)__init_begin;
	for (; addr < (unsigned long)__init_end; addr += PAGE_SIZE) {
		memset((void *)addr, POISON_FREE_INITMEM, PAGE_SIZE);
		ClearPageReserved(virt_to_page(addr));
		init_page_count(virt_to_page(addr));
		free_page(addr);
		totalram_pages++;
	}
	printk ("Freeing unused kernel memory: %luk freed\n",
		((unsigned long)__init_end - (unsigned long)__init_begin) >> 10);
}