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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  kmemcheck_read_strict (struct pt_regs*,unsigned long,unsigned long) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void kmemcheck_read(struct pt_regs *regs,
	unsigned long addr, unsigned int size)
{
	unsigned long page = addr & PAGE_MASK;
	unsigned long next_addr = addr + size - 1;
	unsigned long next_page = next_addr & PAGE_MASK;

	if (likely(page == next_page)) {
		kmemcheck_read_strict(regs, addr, size);
		return;
	}

	/*
	 * What we do is basically to split the access across the
	 * two pages and handle each part separately. Yes, this means
	 * that we may now see reads that are 3 + 5 bytes, for
	 * example (and if both are uninitialized, there will be two
	 * reports), but it makes the code a lot simpler.
	 */
	kmemcheck_read_strict(regs, addr, next_page - addr);
	kmemcheck_read_strict(regs, next_page, next_addr - next_page);
}