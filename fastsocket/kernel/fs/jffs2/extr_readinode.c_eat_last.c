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
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {int /*<<< orphan*/  rb_parent_color; struct rb_node* rb_left; struct rb_node* rb_right; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct rb_node*) ; 
 struct rb_node* rb_parent (struct rb_node*) ; 

__attribute__((used)) static void eat_last(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *parent = rb_parent(node);
	struct rb_node **link;

	/* LAST! */
	BUG_ON(node->rb_right);

	if (!parent)
		link = &root->rb_node;
	else if (node == parent->rb_left)
		link = &parent->rb_left;
	else
		link = &parent->rb_right;

	*link = node->rb_left;
	/* Colour doesn't matter now. Only the parent pointer. */
	if (node->rb_left)
		node->rb_left->rb_parent_color = node->rb_parent_color;
}