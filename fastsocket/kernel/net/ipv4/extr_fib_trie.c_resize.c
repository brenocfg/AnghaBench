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
struct TYPE_2__ {int /*<<< orphan*/  resize_node_skipped; } ;
struct trie {TYPE_1__ stats; } ;
struct tnode {int empty_children; scalar_t__ full_children; int bits; struct node** child; } ;
struct node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tnode*) ; 
 int MAX_WORK ; 
 int /*<<< orphan*/  check_tnode (struct tnode*) ; 
 struct tnode* halve (struct trie*,struct tnode*) ; 
 int halve_threshold ; 
 int halve_threshold_root ; 
 struct tnode* inflate (struct trie*,struct tnode*) ; 
 int inflate_threshold ; 
 int inflate_threshold_root ; 
 int /*<<< orphan*/  node_parent (struct node*) ; 
 int /*<<< orphan*/  node_set_parent (struct node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tnode*,int,int) ; 
 int tnode_child_length (struct tnode*) ; 
 int /*<<< orphan*/  tnode_free_safe (struct tnode*) ; 

__attribute__((used)) static struct node *resize(struct trie *t, struct tnode *tn)
{
	int i;
	struct tnode *old_tn;
	int inflate_threshold_use;
	int halve_threshold_use;
	int max_work;

	if (!tn)
		return NULL;

	pr_debug("In tnode_resize %p inflate_threshold=%d threshold=%d\n",
		 tn, inflate_threshold, halve_threshold);

	/* No children */
	if (tn->empty_children == tnode_child_length(tn)) {
		tnode_free_safe(tn);
		return NULL;
	}
	/* One child */
	if (tn->empty_children == tnode_child_length(tn) - 1)
		goto one_child;
	/*
	 * Double as long as the resulting node has a number of
	 * nonempty nodes that are above the threshold.
	 */

	/*
	 * From "Implementing a dynamic compressed trie" by Stefan Nilsson of
	 * the Helsinki University of Technology and Matti Tikkanen of Nokia
	 * Telecommunications, page 6:
	 * "A node is doubled if the ratio of non-empty children to all
	 * children in the *doubled* node is at least 'high'."
	 *
	 * 'high' in this instance is the variable 'inflate_threshold'. It
	 * is expressed as a percentage, so we multiply it with
	 * tnode_child_length() and instead of multiplying by 2 (since the
	 * child array will be doubled by inflate()) and multiplying
	 * the left-hand side by 100 (to handle the percentage thing) we
	 * multiply the left-hand side by 50.
	 *
	 * The left-hand side may look a bit weird: tnode_child_length(tn)
	 * - tn->empty_children is of course the number of non-null children
	 * in the current node. tn->full_children is the number of "full"
	 * children, that is non-null tnodes with a skip value of 0.
	 * All of those will be doubled in the resulting inflated tnode, so
	 * we just count them one extra time here.
	 *
	 * A clearer way to write this would be:
	 *
	 * to_be_doubled = tn->full_children;
	 * not_to_be_doubled = tnode_child_length(tn) - tn->empty_children -
	 *     tn->full_children;
	 *
	 * new_child_length = tnode_child_length(tn) * 2;
	 *
	 * new_fill_factor = 100 * (not_to_be_doubled + 2*to_be_doubled) /
	 *      new_child_length;
	 * if (new_fill_factor >= inflate_threshold)
	 *
	 * ...and so on, tho it would mess up the while () loop.
	 *
	 * anyway,
	 * 100 * (not_to_be_doubled + 2*to_be_doubled) / new_child_length >=
	 *      inflate_threshold
	 *
	 * avoid a division:
	 * 100 * (not_to_be_doubled + 2*to_be_doubled) >=
	 *      inflate_threshold * new_child_length
	 *
	 * expand not_to_be_doubled and to_be_doubled, and shorten:
	 * 100 * (tnode_child_length(tn) - tn->empty_children +
	 *    tn->full_children) >= inflate_threshold * new_child_length
	 *
	 * expand new_child_length:
	 * 100 * (tnode_child_length(tn) - tn->empty_children +
	 *    tn->full_children) >=
	 *      inflate_threshold * tnode_child_length(tn) * 2
	 *
	 * shorten again:
	 * 50 * (tn->full_children + tnode_child_length(tn) -
	 *    tn->empty_children) >= inflate_threshold *
	 *    tnode_child_length(tn)
	 *
	 */

	check_tnode(tn);

	/* Keep root node larger  */

	if (!node_parent((struct node*) tn)) {
		inflate_threshold_use = inflate_threshold_root;
		halve_threshold_use = halve_threshold_root;
	}
	else {
		inflate_threshold_use = inflate_threshold;
		halve_threshold_use = halve_threshold;
	}

	max_work = MAX_WORK;
	while ((tn->full_children > 0 &&  max_work-- &&
		50 * (tn->full_children + tnode_child_length(tn)
		      - tn->empty_children)
		>= inflate_threshold_use * tnode_child_length(tn))) {

		old_tn = tn;
		tn = inflate(t, tn);

		if (IS_ERR(tn)) {
			tn = old_tn;
#ifdef CONFIG_IP_FIB_TRIE_STATS
			t->stats.resize_node_skipped++;
#endif
			break;
		}
	}

	check_tnode(tn);

	/* Return if at least one inflate is run */
	if( max_work != MAX_WORK)
		return (struct node *) tn;

	/*
	 * Halve as long as the number of empty children in this
	 * node is above threshold.
	 */

	max_work = MAX_WORK;
	while (tn->bits > 1 &&  max_work-- &&
	       100 * (tnode_child_length(tn) - tn->empty_children) <
	       halve_threshold_use * tnode_child_length(tn)) {

		old_tn = tn;
		tn = halve(t, tn);
		if (IS_ERR(tn)) {
			tn = old_tn;
#ifdef CONFIG_IP_FIB_TRIE_STATS
			t->stats.resize_node_skipped++;
#endif
			break;
		}
	}


	/* Only one child remains */
	if (tn->empty_children == tnode_child_length(tn) - 1) {
one_child:
		for (i = 0; i < tnode_child_length(tn); i++) {
			struct node *n;

			n = tn->child[i];
			if (!n)
				continue;

			/* compress one level */

			node_set_parent(n, NULL);
			tnode_free_safe(tn);
			return n;
		}
	}
	return (struct node *) tn;
}