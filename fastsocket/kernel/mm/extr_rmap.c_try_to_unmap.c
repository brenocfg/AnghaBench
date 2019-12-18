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
typedef  enum ttu_flags { ____Placeholder_ttu_flags } ttu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int SWAP_MLOCK ; 
 int SWAP_SUCCESS ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int try_to_unmap_anon (struct page*,int) ; 
 int try_to_unmap_file (struct page*,int) ; 
 int try_to_unmap_ksm (struct page*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int try_to_unmap(struct page *page, enum ttu_flags flags)
{
	int ret;

	BUG_ON(!PageLocked(page));
	VM_BUG_ON(!PageHuge(page) && PageTransHuge(page));

	if (unlikely(PageKsm(page)))
		ret = try_to_unmap_ksm(page, flags);
	else if (PageAnon(page))
		ret = try_to_unmap_anon(page, flags);
	else
		ret = try_to_unmap_file(page, flags);
	if (ret != SWAP_MLOCK && !page_mapped(page))
		ret = SWAP_SUCCESS;
	return ret;
}