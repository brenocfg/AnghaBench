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
 int __GFP_COMP ; 
 int __GFP_NOTRACK ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  kmemleak_alloc (void*,size_t,int,int) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static void *kmalloc_large_node(size_t size, gfp_t flags, int node)
{
	struct page *page;
	void *ptr = NULL;

	flags |= __GFP_COMP | __GFP_NOTRACK;
	page = alloc_pages_node(node, flags, get_order(size));
	if (page)
		ptr = page_address(page);

	kmemleak_alloc(ptr, size, 1, flags);
	return ptr;
}