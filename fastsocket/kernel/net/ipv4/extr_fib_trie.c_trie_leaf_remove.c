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
typedef  int /*<<< orphan*/  t_key ;
struct trie {int /*<<< orphan*/  trie; } ;
struct tnode {int /*<<< orphan*/  bits; int /*<<< orphan*/  pos; } ;
struct node {int dummy; } ;
struct leaf {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_leaf (struct leaf*) ; 
 struct tnode* node_parent (struct node*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct leaf*) ; 
 int /*<<< orphan*/  put_child (struct trie*,struct tnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tkey_extract_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_rebalance (struct trie*,struct tnode*) ; 

__attribute__((used)) static void trie_leaf_remove(struct trie *t, struct leaf *l)
{
	struct tnode *tp = node_parent((struct node *) l);

	pr_debug("entering trie_leaf_remove(%p)\n", l);

	if (tp) {
		t_key cindex = tkey_extract_bits(l->key, tp->pos, tp->bits);
		put_child(t, (struct tnode *)tp, cindex, NULL);
		trie_rebalance(t, tp);
	} else
		rcu_assign_pointer(t->trie, NULL);

	free_leaf(l);
}