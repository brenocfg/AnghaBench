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
struct trie {int /*<<< orphan*/  trie; } ;
struct tnode {int pos; int bits; int /*<<< orphan*/  key; } ;
struct node {int /*<<< orphan*/  key; } ;
struct leaf {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct node*) ; 
 scalar_t__ NODE_TYPE (struct node*) ; 
 scalar_t__ T_TNODE ; 
 int /*<<< orphan*/  check_tnode (struct tnode*) ; 
 struct node* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tkey_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tkey_extract_bits (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ tkey_sub_equals (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct node* tnode_get_child_rcu (struct tnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct leaf *
fib_find_node(struct trie *t, u32 key)
{
	int pos;
	struct tnode *tn;
	struct node *n;

	pos = 0;
	n = rcu_dereference(t->trie);

	while (n != NULL &&  NODE_TYPE(n) == T_TNODE) {
		tn = (struct tnode *) n;

		check_tnode(tn);

		if (tkey_sub_equals(tn->key, pos, tn->pos-pos, key)) {
			pos = tn->pos + tn->bits;
			n = tnode_get_child_rcu(tn,
						tkey_extract_bits(key,
								  tn->pos,
								  tn->bits));
		} else
			break;
	}
	/* Case we have found a leaf. Compare prefixes */

	if (n != NULL && IS_LEAF(n) && tkey_equals(key, n->key))
		return (struct leaf *)n;

	return NULL;
}