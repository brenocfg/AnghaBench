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
struct vm_area_struct {TYPE_1__* vm_mm; int /*<<< orphan*/  anon_vma; } ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_2__ {int /*<<< orphan*/  page_table_lock; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,unsigned long) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mincore_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, unsigned long end,
		unsigned char *vec)
{
	int ret = 0;

	spin_lock(&vma->vm_mm->page_table_lock);
	if (likely(pmd_trans_huge(*pmd))) {
		ret = !pmd_trans_splitting(*pmd);
		spin_unlock(&vma->vm_mm->page_table_lock);
		if (unlikely(!ret))
			wait_split_huge_page(vma->anon_vma, pmd);
		else {
			/*
			 * All logical pages in the range are present
			 * if backed by a huge page.
			 */
			memset(vec, 1, (end - addr) >> PAGE_SHIFT);
		}
	} else
		spin_unlock(&vma->vm_mm->page_table_lock);

	return ret;
}