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
 int DDP_PGIDX_MAX ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned int* ddp_page_order ; 
 unsigned long* ddp_page_shift ; 
 unsigned int get_order (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int ddp_adjust_page_table(void)
{
	int i;
	unsigned int base_order, order;

	if (PAGE_SIZE < (1UL << ddp_page_shift[0])) {
		pr_info("PAGE_SIZE 0x%lx too small, min 0x%lx\n",
			PAGE_SIZE, 1UL << ddp_page_shift[0]);
		return -EINVAL;
	}

	base_order = get_order(1UL << ddp_page_shift[0]);
	order = get_order(1UL << PAGE_SHIFT);

	for (i = 0; i < DDP_PGIDX_MAX; i++) {
		/* first is the kernel page size, then just doubling */
		ddp_page_order[i] = order - base_order + i;
		ddp_page_shift[i] = PAGE_SHIFT + i;
	}
	return 0;
}