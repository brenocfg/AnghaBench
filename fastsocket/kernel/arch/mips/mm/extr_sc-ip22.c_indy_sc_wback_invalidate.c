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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long SC_INDEX (unsigned long) ; 
 unsigned long SC_LINE ; 
 unsigned long SC_SIZE ; 
 int /*<<< orphan*/  indy_sc_wipe (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void indy_sc_wback_invalidate(unsigned long addr, unsigned long size)
{
	unsigned long first_line, last_line;
	unsigned long flags;

#ifdef DEBUG_CACHE
	printk("indy_sc_wback_invalidate[%08lx,%08lx]", addr, size);
#endif

	/* Catch bad driver code */
	BUG_ON(size == 0);

	/* Which lines to flush?  */
	first_line = SC_INDEX(addr);
	last_line = SC_INDEX(addr + size - 1);

	local_irq_save(flags);
	if (first_line <= last_line) {
		indy_sc_wipe(first_line, last_line);
		goto out;
	}

	indy_sc_wipe(first_line, SC_SIZE - SC_LINE);
	indy_sc_wipe(0, last_line);
out:
	local_irq_restore(flags);
}