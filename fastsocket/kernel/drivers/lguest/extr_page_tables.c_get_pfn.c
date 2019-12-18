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
 unsigned long PAGE_SHIFT ; 
 int get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 unsigned long page_to_pfn (struct page*) ; 

__attribute__((used)) static unsigned long get_pfn(unsigned long virtpfn, int write)
{
	struct page *page;

	/* gup me one page at this address please! */
	if (get_user_pages_fast(virtpfn << PAGE_SHIFT, 1, write, &page) == 1)
		return page_to_pfn(page);

	/* This value indicates failure. */
	return -1UL;
}