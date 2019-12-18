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
struct page {int /*<<< orphan*/  objects; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_slabs_node (struct kmem_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_slab (struct kmem_cache*,struct page*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 

__attribute__((used)) static void discard_slab(struct kmem_cache *s, struct page *page)
{
	dec_slabs_node(s, page_to_nid(page), page->objects);
	free_slab(s, page);
}