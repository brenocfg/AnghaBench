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
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  TTU_MUNLOCK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int try_to_unmap_anon (struct page*,int /*<<< orphan*/ ) ; 
 int try_to_unmap_file (struct page*,int /*<<< orphan*/ ) ; 
 int try_to_unmap_ksm (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int try_to_munlock(struct page *page)
{
	VM_BUG_ON(!PageLocked(page) || PageLRU(page));

	if (unlikely(PageKsm(page)))
		return try_to_unmap_ksm(page, TTU_MUNLOCK);
	else if (PageAnon(page))
		return try_to_unmap_anon(page, TTU_MUNLOCK);
	else
		return try_to_unmap_file(page, TTU_MUNLOCK);
}