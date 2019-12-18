#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int id; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ Hash ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PGDIR_MASK ; 
 unsigned long PGDIR_SIZE ; 
 int /*<<< orphan*/  _tlbia () ; 
 int /*<<< orphan*/  flush_hash_pages (unsigned int,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_offset (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void flush_range(struct mm_struct *mm, unsigned long start,
			unsigned long end)
{
	pmd_t *pmd;
	unsigned long pmd_end;
	int count;
	unsigned int ctx = mm->context.id;

	if (Hash == 0) {
		_tlbia();
		return;
	}
	start &= PAGE_MASK;
	if (start >= end)
		return;
	end = (end - 1) | ~PAGE_MASK;
	pmd = pmd_offset(pud_offset(pgd_offset(mm, start), start), start);
	for (;;) {
		pmd_end = ((start + PGDIR_SIZE) & PGDIR_MASK) - 1;
		if (pmd_end > end)
			pmd_end = end;
		if (!pmd_none(*pmd)) {
			count = ((pmd_end - start) >> PAGE_SHIFT) + 1;
			flush_hash_pages(ctx, start, pmd_val(*pmd), count);
		}
		if (pmd_end == end)
			break;
		start = pmd_end + 1;
		++pmd;
	}
}