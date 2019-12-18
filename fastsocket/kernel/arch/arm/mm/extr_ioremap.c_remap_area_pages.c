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
struct mem_type {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long __pfn_to_phys (unsigned long) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int remap_area_pmd (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,struct mem_type const*) ; 

__attribute__((used)) static int remap_area_pages(unsigned long start, unsigned long pfn,
			    size_t size, const struct mem_type *type)
{
	unsigned long addr = start;
	unsigned long next, end = start + size;
	unsigned long phys_addr = __pfn_to_phys(pfn);
	pgd_t *pgd;
	int err = 0;

	BUG_ON(addr >= end);
	pgd = pgd_offset_k(addr);
	do {
		next = pgd_addr_end(addr, end);
		err = remap_area_pmd(pgd, addr, next, phys_addr, type);
		if (err)
			break;
		phys_addr += next - addr;
	} while (pgd++, addr = next, addr != end);

	return err;
}