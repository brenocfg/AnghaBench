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
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  __put_single_page (struct page*) ; 
 int /*<<< orphan*/  put_compound_page (struct page*) ; 
 scalar_t__ put_page_testzero (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void put_page(struct page *page)
{
	if (unlikely(PageCompound(page)))
		put_compound_page(page);
	else if (put_page_testzero(page))
		__put_single_page(page);
}