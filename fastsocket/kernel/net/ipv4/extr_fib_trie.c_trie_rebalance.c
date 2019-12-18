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
struct tnode {int /*<<< orphan*/  bits; int /*<<< orphan*/  pos; int /*<<< orphan*/  key; } ;
struct node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_TNODE (struct tnode*) ; 
 struct tnode* node_parent (struct node*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct node*) ; 
 scalar_t__ resize (struct trie*,struct tnode*) ; 
 int /*<<< orphan*/  tkey_extract_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnode_free_flush () ; 
 int tnode_full (struct tnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnode_get_child (struct tnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnode_put_child_reorg (struct tnode*,int /*<<< orphan*/ ,struct node*,int) ; 

__attribute__((used)) static void trie_rebalance(struct trie *t, struct tnode *tn)
{
	int wasfull;
	t_key cindex, key;
	struct tnode *tp;

	key = tn->key;

	while (tn != NULL && (tp = node_parent((struct node *)tn)) != NULL) {
		cindex = tkey_extract_bits(key, tp->pos, tp->bits);
		wasfull = tnode_full(tp, tnode_get_child(tp, cindex));
		tn = (struct tnode *) resize(t, (struct tnode *)tn);

		tnode_put_child_reorg((struct tnode *)tp, cindex,
				      (struct node *)tn, wasfull);

		tp = node_parent((struct node *) tn);
		if (!tp)
			rcu_assign_pointer(t->trie, (struct node *)tn);

		tnode_free_flush();
		if (!tp)
			break;
		tn = tp;
	}

	/* Handle last (top) tnode */
	if (IS_TNODE(tn))
		tn = (struct tnode *)resize(t, (struct tnode *)tn);

	rcu_assign_pointer(t->trie, (struct node *)tn);
	tnode_free_flush();

	return;
}