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
typedef  enum kmemcheck_shadow { ____Placeholder_kmemcheck_shadow } kmemcheck_shadow ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 void* kmemcheck_shadow_lookup (unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int,unsigned int) ; 

__attribute__((used)) static void mark_shadow(void *address, unsigned int n,
	enum kmemcheck_shadow status)
{
	unsigned long addr = (unsigned long) address;
	unsigned long last_addr = addr + n - 1;
	unsigned long page = addr & PAGE_MASK;
	unsigned long last_page = last_addr & PAGE_MASK;
	unsigned int first_n;
	void *shadow;

	/* If the memory range crosses a page boundary, stop there. */
	if (page == last_page)
		first_n = n;
	else
		first_n = page + PAGE_SIZE - addr;

	shadow = kmemcheck_shadow_lookup(addr);
	if (shadow)
		memset(shadow, status, first_n);

	addr += first_n;
	n -= first_n;

	/* Do full-page memset()s. */
	while (n >= PAGE_SIZE) {
		shadow = kmemcheck_shadow_lookup(addr);
		if (shadow)
			memset(shadow, status, PAGE_SIZE);

		addr += PAGE_SIZE;
		n -= PAGE_SIZE;
	}

	/* Do the remaining page, if any. */
	if (n > 0) {
		shadow = kmemcheck_shadow_lookup(addr);
		if (shadow)
			memset(shadow, status, n);
	}
}