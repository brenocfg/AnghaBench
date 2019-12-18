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
struct anon_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  THP_SPLIT ; 
 int /*<<< orphan*/  __split_huge_page (struct page*,struct anon_vma*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 struct anon_vma* page_lock_anon_vma (struct page*) ; 
 int /*<<< orphan*/  page_unlock_anon_vma (struct anon_vma*) ; 

int split_huge_page(struct page *page)
{
	struct anon_vma *anon_vma;
	int ret = 1;

	BUG_ON(!PageAnon(page));
	anon_vma = page_lock_anon_vma(page);
	if (!anon_vma)
		goto out;
	ret = 0;
	if (!PageCompound(page))
		goto out_unlock;

	BUG_ON(!PageSwapBacked(page));
	__split_huge_page(page, anon_vma);
	count_vm_event(THP_SPLIT);

	BUG_ON(PageCompound(page));
out_unlock:
	page_unlock_anon_vma(anon_vma);
out:
	return ret;
}