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
struct avtab_node {struct avtab_node* next; } ;
struct avtab {int nslot; scalar_t__ mask; struct avtab_node** htable; } ;

/* Variables and functions */
 int /*<<< orphan*/  avtab_node_cachep ; 
 int /*<<< orphan*/  kfree (struct avtab_node**) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct avtab_node*) ; 

void avtab_destroy(struct avtab *h)
{
	int i;
	struct avtab_node *cur, *temp;

	if (!h || !h->htable)
		return;

	for (i = 0; i < h->nslot; i++) {
		cur = h->htable[i];
		while (cur) {
			temp = cur;
			cur = cur->next;
			kmem_cache_free(avtab_node_cachep, temp);
		}
		h->htable[i] = NULL;
	}
	kfree(h->htable);
	h->htable = NULL;
	h->nslot = 0;
	h->mask = 0;
}