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
struct tnode {int bits; struct node** child; int /*<<< orphan*/  full_children; int /*<<< orphan*/  empty_children; } ;
struct node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  node_set_parent (struct node*,struct tnode*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct node*,struct node*) ; 
 int tnode_full (struct tnode*,struct node*) ; 

__attribute__((used)) static void tnode_put_child_reorg(struct tnode *tn, int i, struct node *n,
				  int wasfull)
{
	struct node *chi = tn->child[i];
	int isfull;

	BUG_ON(i >= 1<<tn->bits);

	/* update emptyChildren */
	if (n == NULL && chi != NULL)
		tn->empty_children++;
	else if (n != NULL && chi == NULL)
		tn->empty_children--;

	/* update fullChildren */
	if (wasfull == -1)
		wasfull = tnode_full(tn, chi);

	isfull = tnode_full(tn, n);
	if (wasfull && !isfull)
		tn->full_children--;
	else if (!wasfull && isfull)
		tn->full_children++;

	if (n)
		node_set_parent(n, tn);

	rcu_assign_pointer(tn->child[i], n);
}