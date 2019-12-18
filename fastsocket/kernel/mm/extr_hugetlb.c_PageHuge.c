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
typedef  int /*<<< orphan*/  compound_page_dtor ;

/* Variables and functions */
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/ * free_huge_page ; 
 int /*<<< orphan*/ * get_compound_page_dtor (struct page*) ; 

int PageHuge(struct page *page)
{
	compound_page_dtor *dtor;

	if (!PageCompound(page))
		return 0;

	page = compound_head(page);
	dtor = get_compound_page_dtor(page);

	return dtor == free_huge_page;
}