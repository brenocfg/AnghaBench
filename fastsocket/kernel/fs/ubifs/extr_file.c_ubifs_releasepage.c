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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubifs_releasepage(struct page *page, gfp_t unused_gfp_flags)
{
	/*
	 * An attempt to release a dirty page without budgeting for it - should
	 * not happen.
	 */
	if (PageWriteback(page))
		return 0;
	ubifs_assert(PagePrivate(page));
	ubifs_assert(0);
	ClearPagePrivate(page);
	ClearPageChecked(page);
	return 1;
}