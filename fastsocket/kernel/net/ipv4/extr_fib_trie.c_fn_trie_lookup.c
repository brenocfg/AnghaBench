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
typedef  int t_key ;
struct TYPE_2__ {int /*<<< orphan*/  backtrack; int /*<<< orphan*/  null_node_hit; int /*<<< orphan*/  gets; } ;
struct trie {TYPE_1__ stats; int /*<<< orphan*/  trie; } ;
struct tnode {int pos; int bits; int key; int /*<<< orphan*/ * child; } ;
struct node {int dummy; } ;
struct leaf {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl4_dst; } ;
struct fib_table {scalar_t__ tb_data; } ;
struct fib_result {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct node*) ; 
 int KEYLENGTH ; 
 int check_leaf (struct trie*,struct leaf*,int,struct flowi const*,struct fib_result*) ; 
 int mask_pfx (int,int) ; 
 struct tnode* node_parent_rcu (struct node*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct node* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int tkey_extract_bits (int,int,int) ; 
 struct node* tnode_get_child_rcu (struct tnode*,int) ; 

__attribute__((used)) static int fn_trie_lookup(struct fib_table *tb, const struct flowi *flp,
			  struct fib_result *res)
{
	struct trie *t = (struct trie *) tb->tb_data;
	int ret;
	struct node *n;
	struct tnode *pn;
	int pos, bits;
	t_key key = ntohl(flp->fl4_dst);
	int chopped_off;
	t_key cindex = 0;
	int current_prefix_length = KEYLENGTH;
	struct tnode *cn;
	t_key node_prefix, key_prefix, pref_mismatch;
	int mp;

	rcu_read_lock();

	n = rcu_dereference(t->trie);
	if (!n)
		goto failed;

#ifdef CONFIG_IP_FIB_TRIE_STATS
	t->stats.gets++;
#endif

	/* Just a leaf? */
	if (IS_LEAF(n)) {
		ret = check_leaf(t, (struct leaf *)n, key, flp, res);
		goto found;
	}

	pn = (struct tnode *) n;
	chopped_off = 0;

	while (pn) {
		pos = pn->pos;
		bits = pn->bits;

		if (!chopped_off)
			cindex = tkey_extract_bits(mask_pfx(key, current_prefix_length),
						   pos, bits);

		n = tnode_get_child_rcu(pn, cindex);

		if (n == NULL) {
#ifdef CONFIG_IP_FIB_TRIE_STATS
			t->stats.null_node_hit++;
#endif
			goto backtrace;
		}

		if (IS_LEAF(n)) {
			ret = check_leaf(t, (struct leaf *)n, key, flp, res);
			if (ret > 0)
				goto backtrace;
			goto found;
		}

		cn = (struct tnode *)n;

		/*
		 * It's a tnode, and we can do some extra checks here if we
		 * like, to avoid descending into a dead-end branch.
		 * This tnode is in the parent's child array at index
		 * key[p_pos..p_pos+p_bits] but potentially with some bits
		 * chopped off, so in reality the index may be just a
		 * subprefix, padded with zero at the end.
		 * We can also take a look at any skipped bits in this
		 * tnode - everything up to p_pos is supposed to be ok,
		 * and the non-chopped bits of the index (se previous
		 * paragraph) are also guaranteed ok, but the rest is
		 * considered unknown.
		 *
		 * The skipped bits are key[pos+bits..cn->pos].
		 */

		/* If current_prefix_length < pos+bits, we are already doing
		 * actual prefix  matching, which means everything from
		 * pos+(bits-chopped_off) onward must be zero along some
		 * branch of this subtree - otherwise there is *no* valid
		 * prefix present. Here we can only check the skipped
		 * bits. Remember, since we have already indexed into the
		 * parent's child array, we know that the bits we chopped of
		 * *are* zero.
		 */

		/* NOTA BENE: Checking only skipped bits
		   for the new node here */

		if (current_prefix_length < pos+bits) {
			if (tkey_extract_bits(cn->key, current_prefix_length,
						cn->pos - current_prefix_length)
			    || !(cn->child[0]))
				goto backtrace;
		}

		/*
		 * If chopped_off=0, the index is fully validated and we
		 * only need to look at the skipped bits for this, the new,
		 * tnode. What we actually want to do is to find out if
		 * these skipped bits match our key perfectly, or if we will
		 * have to count on finding a matching prefix further down,
		 * because if we do, we would like to have some way of
		 * verifying the existence of such a prefix at this point.
		 */

		/* The only thing we can do at this point is to verify that
		 * any such matching prefix can indeed be a prefix to our
		 * key, and if the bits in the node we are inspecting that
		 * do not match our key are not ZERO, this cannot be true.
		 * Thus, find out where there is a mismatch (before cn->pos)
		 * and verify that all the mismatching bits are zero in the
		 * new tnode's key.
		 */

		/*
		 * Note: We aren't very concerned about the piece of
		 * the key that precede pn->pos+pn->bits, since these
		 * have already been checked. The bits after cn->pos
		 * aren't checked since these are by definition
		 * "unknown" at this point. Thus, what we want to see
		 * is if we are about to enter the "prefix matching"
		 * state, and in that case verify that the skipped
		 * bits that will prevail throughout this subtree are
		 * zero, as they have to be if we are to find a
		 * matching prefix.
		 */

		node_prefix = mask_pfx(cn->key, cn->pos);
		key_prefix = mask_pfx(key, cn->pos);
		pref_mismatch = key_prefix^node_prefix;
		mp = 0;

		/*
		 * In short: If skipped bits in this node do not match
		 * the search key, enter the "prefix matching"
		 * state.directly.
		 */
		if (pref_mismatch) {
			while (!(pref_mismatch & (1<<(KEYLENGTH-1)))) {
				mp++;
				pref_mismatch = pref_mismatch << 1;
			}
			key_prefix = tkey_extract_bits(cn->key, mp, cn->pos-mp);

			if (key_prefix != 0)
				goto backtrace;

			if (current_prefix_length >= cn->pos)
				current_prefix_length = mp;
		}

		pn = (struct tnode *)n; /* Descend */
		chopped_off = 0;
		continue;

backtrace:
		chopped_off++;

		/* As zero don't change the child key (cindex) */
		while ((chopped_off <= pn->bits)
		       && !(cindex & (1<<(chopped_off-1))))
			chopped_off++;

		/* Decrease current_... with bits chopped off */
		if (current_prefix_length > pn->pos + pn->bits - chopped_off)
			current_prefix_length = pn->pos + pn->bits
				- chopped_off;

		/*
		 * Either we do the actual chop off according or if we have
		 * chopped off all bits in this tnode walk up to our parent.
		 */

		if (chopped_off <= pn->bits) {
			cindex &= ~(1 << (chopped_off-1));
		} else {
			struct tnode *parent = node_parent_rcu((struct node *) pn);
			if (!parent)
				goto failed;

			/* Get Child's index */
			cindex = tkey_extract_bits(pn->key, parent->pos, parent->bits);
			pn = parent;
			chopped_off = 0;

#ifdef CONFIG_IP_FIB_TRIE_STATS
			t->stats.backtrack++;
#endif
			goto backtrace;
		}
	}
failed:
	ret = 1;
found:
	rcu_read_unlock();
	return ret;
}