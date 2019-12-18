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
struct virtual_node {int vn_nr_item; } ;
struct tree_balance {int* insert_size; int* lnum; int lbytes; int* rnum; int rbytes; int s0num; int /*<<< orphan*/ * FL; int /*<<< orphan*/ * FR; int /*<<< orphan*/  tb_path; struct virtual_node* tb_vn; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_FREE_SPACE (struct buffer_head*) ; 
 int CARRY_ON ; 
 int MAX_CHILD_SIZE (struct buffer_head*) ; 
 int NO_BALANCING_NEEDED ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 scalar_t__ are_leaves_removable (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  check_left (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  check_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  create_virtual_node (struct tree_balance*,int) ; 
 int get_lfree (struct tree_balance*,int) ; 
 int get_parents (struct tree_balance*,int) ; 
 int get_rfree (struct tree_balance*,int) ; 
 scalar_t__ is_leaf_removable (struct tree_balance*) ; 
 scalar_t__ is_left_neighbor_in_cache (struct tree_balance*,int) ; 
 int /*<<< orphan*/  set_parameters (struct tree_balance*,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dc_check_balance_leaf(struct tree_balance *tb, int h)
{
	struct virtual_node *vn = tb->tb_vn;

	/* Number of bytes that must be deleted from
	   (value is negative if bytes are deleted) buffer which
	   contains node being balanced.  The mnemonic is that the
	   attempted change in node space used level is levbytes bytes. */
	int levbytes;
	/* the maximal item size */
	int maxsize, ret;
	/* S0 is the node whose balance is currently being checked,
	   and F0 is its father.  */
	struct buffer_head *S0, *F0;
	int lfree, rfree /* free space in L and R */ ;

	S0 = PATH_H_PBUFFER(tb->tb_path, 0);
	F0 = PATH_H_PPARENT(tb->tb_path, 0);

	levbytes = tb->insert_size[h];

	maxsize = MAX_CHILD_SIZE(S0);	/* maximal possible size of an item */

	if (!F0) {		/* S[0] is the root now. */

		RFALSE(-levbytes >= maxsize - B_FREE_SPACE(S0),
		       "vs-8240: attempt to create empty buffer tree");

		set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
		return NO_BALANCING_NEEDED;
	}

	if ((ret = get_parents(tb, h)) != CARRY_ON)
		return ret;

	/* get free space of neighbors */
	rfree = get_rfree(tb, h);
	lfree = get_lfree(tb, h);

	create_virtual_node(tb, h);

	/* if 3 leaves can be merge to one, set parameters and return */
	if (are_leaves_removable(tb, lfree, rfree))
		return CARRY_ON;

	/* determine maximal number of items we can shift to the left/right  neighbor
	   and the maximal number of bytes that can flow to the left/right neighbor
	   from the left/right most liquid item that cannot be shifted from S[0] entirely
	 */
	check_left(tb, h, lfree);
	check_right(tb, h, rfree);

	/* check whether we can merge S with left neighbor. */
	if (tb->lnum[0] >= vn->vn_nr_item && tb->lbytes == -1)
		if (is_left_neighbor_in_cache(tb, h) || ((tb->rnum[0] - ((tb->rbytes == -1) ? 0 : 1)) < vn->vn_nr_item) ||	/* S can not be merged with R */
		    !tb->FR[h]) {

			RFALSE(!tb->FL[h],
			       "vs-8245: dc_check_balance_leaf: FL[h] must exist");

			/* set parameter to merge S[0] with its left neighbor */
			set_parameters(tb, h, -1, 0, 0, NULL, -1, -1);
			return CARRY_ON;
		}

	/* check whether we can merge S[0] with right neighbor. */
	if (tb->rnum[0] >= vn->vn_nr_item && tb->rbytes == -1) {
		set_parameters(tb, h, 0, -1, 0, NULL, -1, -1);
		return CARRY_ON;
	}

	/* All contents of S[0] can be moved to the neighbors (L[0] & R[0]). Set parameters and return */
	if (is_leaf_removable(tb))
		return CARRY_ON;

	/* Balancing is not required. */
	tb->s0num = vn->vn_nr_item;
	set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
	return NO_BALANCING_NEEDED;
}