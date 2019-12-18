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
typedef  int t_key ;
struct trie {int dummy; } ;
struct tnode {int key; int pos; int bits; struct node** child; } ;
struct node {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tnode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LEAF (struct node*) ; 
 scalar_t__ IS_TNODE (struct tnode*) ; 
 int KEYLENGTH ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_child (struct trie*,struct tnode*,int,struct node*) ; 
 struct node* resize (struct trie*,struct tnode*) ; 
 scalar_t__ tkey_extract_bits (int /*<<< orphan*/ ,int,int) ; 
 int tnode_child_length (struct tnode*) ; 
 int /*<<< orphan*/  tnode_free (struct tnode*) ; 
 int /*<<< orphan*/  tnode_free_safe (struct tnode*) ; 
 struct node* tnode_get_child (struct tnode*,int) ; 
 struct tnode* tnode_new (int,int,int) ; 

__attribute__((used)) static struct tnode *inflate(struct trie *t, struct tnode *tn)
{
	struct tnode *oldtnode = tn;
	int olen = tnode_child_length(tn);
	int i;

	pr_debug("In inflate\n");

	tn = tnode_new(oldtnode->key, oldtnode->pos, oldtnode->bits + 1);

	if (!tn)
		return ERR_PTR(-ENOMEM);

	/*
	 * Preallocate and store tnodes before the actual work so we
	 * don't get into an inconsistent state if memory allocation
	 * fails. In case of failure we return the oldnode and  inflate
	 * of tnode is ignored.
	 */

	for (i = 0; i < olen; i++) {
		struct tnode *inode;

		inode = (struct tnode *) tnode_get_child(oldtnode, i);
		if (inode &&
		    IS_TNODE(inode) &&
		    inode->pos == oldtnode->pos + oldtnode->bits &&
		    inode->bits > 1) {
			struct tnode *left, *right;
			t_key m = ~0U << (KEYLENGTH - 1) >> inode->pos;

			left = tnode_new(inode->key&(~m), inode->pos + 1,
					 inode->bits - 1);
			if (!left)
				goto nomem;

			right = tnode_new(inode->key|m, inode->pos + 1,
					  inode->bits - 1);

			if (!right) {
				tnode_free(left);
				goto nomem;
			}

			put_child(t, tn, 2*i, (struct node *) left);
			put_child(t, tn, 2*i+1, (struct node *) right);
		}
	}

	for (i = 0; i < olen; i++) {
		struct tnode *inode;
		struct node *node = tnode_get_child(oldtnode, i);
		struct tnode *left, *right;
		int size, j;

		/* An empty child */
		if (node == NULL)
			continue;

		/* A leaf or an internal node with skipped bits */

		if (IS_LEAF(node) || ((struct tnode *) node)->pos >
		   tn->pos + tn->bits - 1) {
			if (tkey_extract_bits(node->key,
					      oldtnode->pos + oldtnode->bits,
					      1) == 0)
				put_child(t, tn, 2*i, node);
			else
				put_child(t, tn, 2*i+1, node);
			continue;
		}

		/* An internal node with two children */
		inode = (struct tnode *) node;

		if (inode->bits == 1) {
			put_child(t, tn, 2*i, inode->child[0]);
			put_child(t, tn, 2*i+1, inode->child[1]);

			tnode_free_safe(inode);
			continue;
		}

		/* An internal node with more than two children */

		/* We will replace this node 'inode' with two new
		 * ones, 'left' and 'right', each with half of the
		 * original children. The two new nodes will have
		 * a position one bit further down the key and this
		 * means that the "significant" part of their keys
		 * (see the discussion near the top of this file)
		 * will differ by one bit, which will be "0" in
		 * left's key and "1" in right's key. Since we are
		 * moving the key position by one step, the bit that
		 * we are moving away from - the bit at position
		 * (inode->pos) - is the one that will differ between
		 * left and right. So... we synthesize that bit in the
		 * two  new keys.
		 * The mask 'm' below will be a single "one" bit at
		 * the position (inode->pos)
		 */

		/* Use the old key, but set the new significant
		 *   bit to zero.
		 */

		left = (struct tnode *) tnode_get_child(tn, 2*i);
		put_child(t, tn, 2*i, NULL);

		BUG_ON(!left);

		right = (struct tnode *) tnode_get_child(tn, 2*i+1);
		put_child(t, tn, 2*i+1, NULL);

		BUG_ON(!right);

		size = tnode_child_length(left);
		for (j = 0; j < size; j++) {
			put_child(t, left, j, inode->child[j]);
			put_child(t, right, j, inode->child[j + size]);
		}
		put_child(t, tn, 2*i, resize(t, left));
		put_child(t, tn, 2*i+1, resize(t, right));

		tnode_free_safe(inode);
	}
	tnode_free_safe(oldtnode);
	return tn;
nomem:
	{
		int size = tnode_child_length(tn);
		int j;

		for (j = 0; j < size; j++)
			if (tn->child[j])
				tnode_free((struct tnode *)tn->child[j]);

		tnode_free(tn);

		return ERR_PTR(-ENOMEM);
	}
}