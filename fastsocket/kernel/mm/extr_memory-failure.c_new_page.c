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
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 scalar_t__ PageHuge (struct page*) ; 
 struct page* alloc_huge_page_node (int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages_exact_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 int /*<<< orphan*/  page_hstate (int /*<<< orphan*/ ) ; 
 int page_to_nid (struct page*) ; 

__attribute__((used)) static struct page *new_page(struct page *p, unsigned long private, int **x)
{
	int nid = page_to_nid(p);
	if (PageHuge(p))
		return alloc_huge_page_node(page_hstate(compound_head(p)),
						   nid);
	else
		return alloc_pages_exact_node(nid, GFP_HIGHUSER_MOVABLE, 0);
}