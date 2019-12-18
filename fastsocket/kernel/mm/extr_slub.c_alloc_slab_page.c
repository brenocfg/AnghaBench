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
struct kmem_cache_order_objects {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __GFP_NOTRACK ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int) ; 
 int oo_order (struct kmem_cache_order_objects) ; 

__attribute__((used)) static inline struct page *alloc_slab_page(gfp_t flags, int node,
					struct kmem_cache_order_objects oo)
{
	int order = oo_order(oo);

	flags |= __GFP_NOTRACK;

	if (node == -1)
		return alloc_pages(flags, order);
	else
		return alloc_pages_node(node, flags, order);
}