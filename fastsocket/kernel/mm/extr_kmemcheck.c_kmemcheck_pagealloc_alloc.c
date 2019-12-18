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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_HIGHMEM ; 
 int __GFP_NOTRACK ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  kmemcheck_alloc_shadow (struct page*,unsigned int,int,int) ; 
 int /*<<< orphan*/  kmemcheck_mark_initialized_pages (struct page*,int) ; 
 int /*<<< orphan*/  kmemcheck_mark_uninitialized_pages (struct page*,int) ; 

void kmemcheck_pagealloc_alloc(struct page *page, unsigned int order,
			       gfp_t gfpflags)
{
	int pages;

	if (gfpflags & (__GFP_HIGHMEM | __GFP_NOTRACK))
		return;

	pages = 1 << order;

	/*
	 * NOTE: We choose to track GFP_ZERO pages too; in fact, they
	 * can become uninitialized by copying uninitialized memory
	 * into them.
	 */

	/* XXX: Can use zone->node for node? */
	kmemcheck_alloc_shadow(page, order, gfpflags, -1);

	if (gfpflags & __GFP_ZERO)
		kmemcheck_mark_initialized_pages(page, pages);
	else
		kmemcheck_mark_uninitialized_pages(page, pages);
}