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
struct device_node {TYPE_1__* parent; struct device_node* allnext; struct device_node* sibling; } ;
struct TYPE_2__ {struct device_node* child; } ;

/* Variables and functions */
 struct device_node* allnodes ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void of_attach_node(struct device_node *np)
{
	unsigned long flags;

	write_lock_irqsave(&devtree_lock, flags);
	np->sibling = np->parent->child;
	np->allnext = allnodes;
	np->parent->child = np;
	allnodes = np;
	write_unlock_irqrestore(&devtree_lock, flags);
}