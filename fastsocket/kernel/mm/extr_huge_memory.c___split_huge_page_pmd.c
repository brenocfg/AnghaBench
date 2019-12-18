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
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

void __split_huge_page_pmd(struct mm_struct *mm, pmd_t *pmd)
{
	struct page *page;

	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_trans_huge(*pmd))) {
		spin_unlock(&mm->page_table_lock);
		return;
	}
	page = pmd_page(*pmd);
	VM_BUG_ON(!page_count(page));
	get_page(page);
	spin_unlock(&mm->page_table_lock);

	split_huge_page(page);

	put_page(page);
	BUG_ON(pmd_trans_huge(*pmd));
}