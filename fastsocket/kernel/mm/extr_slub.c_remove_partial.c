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
struct page {int /*<<< orphan*/  lru; } ;
struct kmem_cache_node {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  nr_partial; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 struct kmem_cache_node* get_node (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_partial(struct kmem_cache *s, struct page *page)
{
	struct kmem_cache_node *n = get_node(s, page_to_nid(page));

	spin_lock(&n->list_lock);
	list_del(&page->lru);
	n->nr_partial--;
	spin_unlock(&n->list_lock);
}