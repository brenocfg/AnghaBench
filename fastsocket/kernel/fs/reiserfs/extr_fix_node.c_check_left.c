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
struct virtual_node {int vn_nr_item; unsigned int vn_size; scalar_t__ vn_mode; struct virtual_item* vn_vi; } ;
struct virtual_item {int vi_type; scalar_t__ vi_item_len; } ;
struct tree_balance {int* lnum; int lbytes; int /*<<< orphan*/  tb_path; struct virtual_node* tb_vn; } ;

/* Variables and functions */
 int DC_SIZE ; 
 unsigned int IH_SIZE ; 
 int KEY_SIZE ; 
 scalar_t__ M_INSERT ; 
 scalar_t__ M_PASTE ; 
 int /*<<< orphan*/  PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int VI_TYPE_LEFT_MERGEABLE ; 
 int op_check_left (struct virtual_item*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_left(struct tree_balance *tb, int h, int cur_free)
{
	int i;
	struct virtual_node *vn = tb->tb_vn;
	struct virtual_item *vi;
	int d_size, ih_size;

	RFALSE(cur_free < 0, "vs-8050: cur_free (%d) < 0", cur_free);

	/* internal level */
	if (h > 0) {
		tb->lnum[h] = cur_free / (DC_SIZE + KEY_SIZE);
		return;
	}

	/* leaf level */

	if (!cur_free || !vn->vn_nr_item) {
		/* no free space or nothing to move */
		tb->lnum[h] = 0;
		tb->lbytes = -1;
		return;
	}

	RFALSE(!PATH_H_PPARENT(tb->tb_path, 0),
	       "vs-8055: parent does not exist or invalid");

	vi = vn->vn_vi;
	if ((unsigned int)cur_free >=
	    (vn->vn_size -
	     ((vi->vi_type & VI_TYPE_LEFT_MERGEABLE) ? IH_SIZE : 0))) {
		/* all contents of S[0] fits into L[0] */

		RFALSE(vn->vn_mode == M_INSERT || vn->vn_mode == M_PASTE,
		       "vs-8055: invalid mode or balance condition failed");

		tb->lnum[0] = vn->vn_nr_item;
		tb->lbytes = -1;
		return;
	}

	d_size = 0, ih_size = IH_SIZE;

	/* first item may be merge with last item in left neighbor */
	if (vi->vi_type & VI_TYPE_LEFT_MERGEABLE)
		d_size = -((int)IH_SIZE), ih_size = 0;

	tb->lnum[0] = 0;
	for (i = 0; i < vn->vn_nr_item;
	     i++, ih_size = IH_SIZE, d_size = 0, vi++) {
		d_size += vi->vi_item_len;
		if (cur_free >= d_size) {
			/* the item can be shifted entirely */
			cur_free -= d_size;
			tb->lnum[0]++;
			continue;
		}

		/* the item cannot be shifted entirely, try to split it */
		/* check whether L[0] can hold ih and at least one byte of the item body */
		if (cur_free <= ih_size) {
			/* cannot shift even a part of the current item */
			tb->lbytes = -1;
			return;
		}
		cur_free -= ih_size;

		tb->lbytes = op_check_left(vi, cur_free, 0, 0);
		if (tb->lbytes != -1)
			/* count partially shifted item */
			tb->lnum[0]++;

		break;
	}

	return;
}