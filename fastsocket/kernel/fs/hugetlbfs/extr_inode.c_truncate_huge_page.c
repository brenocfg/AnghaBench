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
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remove_from_page_cache (struct page*) ; 

__attribute__((used)) static void truncate_huge_page(struct page *page)
{
	cancel_dirty_page(page, /* No IO accounting for huge pages? */0);
	ClearPageUptodate(page);
	remove_from_page_cache(page);
	put_page(page);
}