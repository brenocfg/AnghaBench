#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct rb_node* rb_node; } ;
struct rblist {int (* node_cmp ) (struct rb_node*,void const*) ;TYPE_1__ entries; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 int stub1 (struct rb_node*,void const*) ; 

struct rb_node *rblist__find(struct rblist *rblist, const void *entry)
{
	struct rb_node **p = &rblist->entries.rb_node;
	struct rb_node *parent = NULL;

	while (*p != NULL) {
		int rc;

		parent = *p;

		rc = rblist->node_cmp(parent, entry);
		if (rc > 0)
			p = &(*p)->rb_left;
		else if (rc < 0)
			p = &(*p)->rb_right;
		else
			return parent;
	}

	return NULL;
}