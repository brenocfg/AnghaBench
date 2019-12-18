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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_fn_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int apply_to_pud_range (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 

int apply_to_page_range(struct mm_struct *mm, unsigned long addr,
			unsigned long size, pte_fn_t fn, void *data)
{
	pgd_t *pgd;
	unsigned long next;
	unsigned long start = addr, end = addr + size;
	int err;

	BUG_ON(addr >= end);
	mmu_notifier_invalidate_range_start(mm, start, end);
	pgd = pgd_offset(mm, addr);
	do {
		next = pgd_addr_end(addr, end);
		err = apply_to_pud_range(mm, pgd, addr, next, fn, data);
		if (err)
			break;
	} while (pgd++, addr = next, addr != end);
	mmu_notifier_invalidate_range_end(mm, start, end);
	return err;
}