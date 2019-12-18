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
struct ebitmap_node {struct ebitmap_node* next; } ;
struct ebitmap {struct ebitmap_node* node; scalar_t__ highbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ebitmap_node*) ; 

void ebitmap_destroy(struct ebitmap *e)
{
	struct ebitmap_node *n, *temp;

	if (!e)
		return;

	n = e->node;
	while (n) {
		temp = n;
		n = n->next;
		kfree(temp);
	}

	e->highbit = 0;
	e->node = NULL;
	return;
}