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
struct tnode {int dummy; } ;
struct node {int dummy; } ;
struct leaf {int dummy; } ;

/* Variables and functions */
 struct leaf* leaf_walk_rcu (struct tnode*,struct node*) ; 
 struct tnode* node_parent_rcu (struct node*) ; 

__attribute__((used)) static struct leaf *trie_nextleaf(struct leaf *l)
{
	struct node *c = (struct node *) l;
	struct tnode *p = node_parent_rcu(c);

	if (!p)
		return NULL;	/* trie with just one leaf */

	return leaf_walk_rcu(p, c);
}