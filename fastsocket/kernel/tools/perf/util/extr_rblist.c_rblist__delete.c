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
struct rblist {int /*<<< orphan*/  entries; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rblist*) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 int /*<<< orphan*/  rblist__remove_node (struct rblist*,struct rb_node*) ; 

void rblist__delete(struct rblist *rblist)
{
	if (rblist != NULL) {
		struct rb_node *pos, *next = rb_first(&rblist->entries);

		while (next) {
			pos = next;
			next = rb_next(pos);
			rblist__remove_node(rblist, pos);
		}
		free(rblist);
	}
}