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

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  SetPageHWPoison (struct page*) ; 
 int __soft_offline_page (struct page*,int) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct page* compound_trans_head (struct page*) ; 
 int compound_trans_order (struct page*) ; 
 int /*<<< orphan*/  dequeue_hwpoisoned_huge_page (struct page*) ; 
 int get_any_page (struct page*,unsigned long,int) ; 
 int /*<<< orphan*/  num_poisoned_pages ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  set_page_hwpoison_huge_page (struct page*) ; 
 int soft_offline_huge_page (struct page*,int) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int soft_offline_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);
	struct page *hpage = compound_trans_head(page);

	if (PageHWPoison(page)) {
		pr_info("soft offline: %#lx page already poisoned\n", pfn);
		return -EBUSY;
	}
	if (!PageHuge(page) && PageTransHuge(hpage)) {
		if (PageAnon(hpage) && unlikely(split_huge_page(hpage))) {
			pr_info("soft offline: %#lx: failed to split THP\n",
				pfn);
			return -EBUSY;
		}
	}

	ret = get_any_page(page, pfn, flags);
	if (ret < 0)
		return ret;
	if (ret) { /* for in-use pages */
		if (PageHuge(page))
			ret = soft_offline_huge_page(page, flags);
		else
			ret = __soft_offline_page(page, flags);
	} else { /* for free pages */
		if (PageHuge(page)) {
			set_page_hwpoison_huge_page(hpage);
			dequeue_hwpoisoned_huge_page(hpage);
			atomic_long_add(1 << compound_trans_order(hpage),
					&num_poisoned_pages);
		} else {
			SetPageHWPoison(page);
			atomic_long_inc(&num_poisoned_pages);
		}
	}
	return ret;
}