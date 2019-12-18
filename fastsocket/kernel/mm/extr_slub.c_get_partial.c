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
struct kmem_cache {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_THISNODE ; 
 struct page* get_any_partial (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  get_node (struct kmem_cache*,int) ; 
 struct page* get_partial_node (int /*<<< orphan*/ ) ; 
 int numa_node_id () ; 

__attribute__((used)) static struct page *get_partial(struct kmem_cache *s, gfp_t flags, int node)
{
	struct page *page;
	int searchnode = (node == -1) ? numa_node_id() : node;

	page = get_partial_node(get_node(s, searchnode));
	if (page || (flags & __GFP_THISNODE))
		return page;

	return get_any_partial(s, flags);
}