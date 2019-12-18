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
typedef  int /*<<< orphan*/  u32 ;
typedef  int t_key ;
struct trie {struct tnode* trie; } ;
struct tnode {int pos; int bits; int /*<<< orphan*/  key; } ;
struct node {int pos; int bits; int /*<<< orphan*/  key; } ;
struct list_head {int dummy; } ;
struct leaf_info {struct list_head falh; } ;
struct leaf {int /*<<< orphan*/  list; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_LEAF (struct tnode*) ; 
 scalar_t__ NODE_TYPE (struct tnode*) ; 
 scalar_t__ T_TNODE ; 
 int /*<<< orphan*/  check_tnode (struct tnode*) ; 
 int /*<<< orphan*/  free_leaf (struct leaf*) ; 
 int /*<<< orphan*/  free_leaf_info (struct leaf_info*) ; 
 int /*<<< orphan*/  insert_leaf_info (int /*<<< orphan*/ *,struct leaf_info*) ; 
 struct leaf_info* leaf_info_new (int) ; 
 struct leaf* leaf_new () ; 
 struct tnode* node_parent (struct tnode*) ; 
 int /*<<< orphan*/  node_set_parent (struct tnode*,struct tnode*) ; 
 int /*<<< orphan*/  pr_warning (char*,struct tnode*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_child (struct trie*,struct tnode*,int,struct tnode*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct tnode*,struct tnode*) ; 
 scalar_t__ tkey_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tkey_extract_bits (int /*<<< orphan*/ ,int,int) ; 
 int tkey_mismatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tkey_sub_equals (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct tnode* tnode_get_child (struct tnode*,int) ; 
 struct tnode* tnode_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trie_rebalance (struct trie*,struct tnode*) ; 

__attribute__((used)) static struct list_head *fib_insert_node(struct trie *t, u32 key, int plen)
{
	int pos, newpos;
	struct tnode *tp = NULL, *tn = NULL;
	struct node *n;
	struct leaf *l;
	int missbit;
	struct list_head *fa_head = NULL;
	struct leaf_info *li;
	t_key cindex;

	pos = 0;
	n = t->trie;

	/* If we point to NULL, stop. Either the tree is empty and we should
	 * just put a new leaf in if, or we have reached an empty child slot,
	 * and we should just put our new leaf in that.
	 * If we point to a T_TNODE, check if it matches our key. Note that
	 * a T_TNODE might be skipping any number of bits - its 'pos' need
	 * not be the parent's 'pos'+'bits'!
	 *
	 * If it does match the current key, get pos/bits from it, extract
	 * the index from our key, push the T_TNODE and walk the tree.
	 *
	 * If it doesn't, we have to replace it with a new T_TNODE.
	 *
	 * If we point to a T_LEAF, it might or might not have the same key
	 * as we do. If it does, just change the value, update the T_LEAF's
	 * value, and return it.
	 * If it doesn't, we need to replace it with a T_TNODE.
	 */

	while (n != NULL &&  NODE_TYPE(n) == T_TNODE) {
		tn = (struct tnode *) n;

		check_tnode(tn);

		if (tkey_sub_equals(tn->key, pos, tn->pos-pos, key)) {
			tp = tn;
			pos = tn->pos + tn->bits;
			n = tnode_get_child(tn,
					    tkey_extract_bits(key,
							      tn->pos,
							      tn->bits));

			BUG_ON(n && node_parent(n) != tn);
		} else
			break;
	}

	/*
	 * n  ----> NULL, LEAF or TNODE
	 *
	 * tp is n's (parent) ----> NULL or TNODE
	 */

	BUG_ON(tp && IS_LEAF(tp));

	/* Case 1: n is a leaf. Compare prefixes */

	if (n != NULL && IS_LEAF(n) && tkey_equals(key, n->key)) {
		l = (struct leaf *) n;
		li = leaf_info_new(plen);

		if (!li)
			return NULL;

		fa_head = &li->falh;
		insert_leaf_info(&l->list, li);
		goto done;
	}
	l = leaf_new();

	if (!l)
		return NULL;

	l->key = key;
	li = leaf_info_new(plen);

	if (!li) {
		free_leaf(l);
		return NULL;
	}

	fa_head = &li->falh;
	insert_leaf_info(&l->list, li);

	if (t->trie && n == NULL) {
		/* Case 2: n is NULL, and will just insert a new leaf */

		node_set_parent((struct node *)l, tp);

		cindex = tkey_extract_bits(key, tp->pos, tp->bits);
		put_child(t, (struct tnode *)tp, cindex, (struct node *)l);
	} else {
		/* Case 3: n is a LEAF or a TNODE and the key doesn't match. */
		/*
		 *  Add a new tnode here
		 *  first tnode need some special handling
		 */

		if (tp)
			pos = tp->pos+tp->bits;
		else
			pos = 0;

		if (n) {
			newpos = tkey_mismatch(key, pos, n->key);
			tn = tnode_new(n->key, newpos, 1);
		} else {
			newpos = 0;
			tn = tnode_new(key, newpos, 1); /* First tnode */
		}

		if (!tn) {
			free_leaf_info(li);
			free_leaf(l);
			return NULL;
		}

		node_set_parent((struct node *)tn, tp);

		missbit = tkey_extract_bits(key, newpos, 1);
		put_child(t, tn, missbit, (struct node *)l);
		put_child(t, tn, 1-missbit, n);

		if (tp) {
			cindex = tkey_extract_bits(key, tp->pos, tp->bits);
			put_child(t, (struct tnode *)tp, cindex,
				  (struct node *)tn);
		} else {
			rcu_assign_pointer(t->trie, (struct node *)tn);
			tp = tn;
		}
	}

	if (tp && tp->pos + tp->bits > 32)
		pr_warning("fib_trie"
			   " tp=%p pos=%d, bits=%d, key=%0x plen=%d\n",
			   tp, tp->pos, tp->bits, key, plen);

	/* Rebalance the trie */

	trie_rebalance(t, tp);
done:
	return fa_head;
}