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
struct tree_balance {int* insert_size; int* blknum; int* lnum; int* rnum; int /*<<< orphan*/  tb_sb; struct buffer_head** R; struct buffer_head** L; int /*<<< orphan*/  tb_path; } ;
struct buffer_info {int /*<<< orphan*/  bi_parent; int /*<<< orphan*/  bi_position; struct buffer_head* bi_bh; struct tree_balance* tb; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; } ;

/* Variables and functions */
 scalar_t__ B_FREE_SPACE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ DC_SIZE ; 
 int /*<<< orphan*/  INTERNAL_SHIFT_FROM_L_TO_S ; 
 int /*<<< orphan*/  INTERNAL_SHIFT_FROM_R_TO_S ; 
 int /*<<< orphan*/  INTERNAL_SHIFT_FROM_S_TO_L ; 
 int /*<<< orphan*/  INTERNAL_SHIFT_FROM_S_TO_R ; 
 scalar_t__ KEY_SIZE ; 
 scalar_t__ MAX_CHILD_SIZE (struct buffer_head*) ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PATH_H_PPARENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PUT_SB_ROOT_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SB_TREE_HEIGHT (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,...) ; 
 scalar_t__ SB_TREE_HEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_internal (struct buffer_head*) ; 
 int /*<<< orphan*/  do_balance_mark_sb_dirty (struct tree_balance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  internal_delete_childs (struct buffer_info*,int,int) ; 
 int /*<<< orphan*/  internal_shift_left (int /*<<< orphan*/ ,struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  internal_shift_right (int /*<<< orphan*/ ,struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  reiserfs_invalidate_buffer (struct tree_balance*,struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 

__attribute__((used)) static void balance_internal_when_delete(struct tree_balance *tb,
					 int h, int child_pos)
{
	int insert_num;
	int n;
	struct buffer_head *tbSh = PATH_H_PBUFFER(tb->tb_path, h);
	struct buffer_info bi;

	insert_num = tb->insert_size[h] / ((int)(DC_SIZE + KEY_SIZE));

	/* delete child-node-pointer(s) together with their left item(s) */
	bi.tb = tb;
	bi.bi_bh = tbSh;
	bi.bi_parent = PATH_H_PPARENT(tb->tb_path, h);
	bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);

	internal_delete_childs(&bi, child_pos, -insert_num);

	RFALSE(tb->blknum[h] > 1,
	       "tb->blknum[%d]=%d when insert_size < 0", h, tb->blknum[h]);

	n = B_NR_ITEMS(tbSh);

	if (tb->lnum[h] == 0 && tb->rnum[h] == 0) {
		if (tb->blknum[h] == 0) {
			/* node S[h] (root of the tree) is empty now */
			struct buffer_head *new_root;

			RFALSE(n
			       || B_FREE_SPACE(tbSh) !=
			       MAX_CHILD_SIZE(tbSh) - DC_SIZE,
			       "buffer must have only 0 keys (%d)", n);
			RFALSE(bi.bi_parent, "root has parent (%p)",
			       bi.bi_parent);

			/* choose a new root */
			if (!tb->L[h - 1] || !B_NR_ITEMS(tb->L[h - 1]))
				new_root = tb->R[h - 1];
			else
				new_root = tb->L[h - 1];
			/* switch super block's tree root block number to the new value */
			PUT_SB_ROOT_BLOCK(tb->tb_sb, new_root->b_blocknr);
			//REISERFS_SB(tb->tb_sb)->s_rs->s_tree_height --;
			PUT_SB_TREE_HEIGHT(tb->tb_sb,
					   SB_TREE_HEIGHT(tb->tb_sb) - 1);

			do_balance_mark_sb_dirty(tb,
						 REISERFS_SB(tb->tb_sb)->s_sbh,
						 1);
			/*&&&&&&&&&&&&&&&&&&&&&& */
			if (h > 1)
				/* use check_internal if new root is an internal node */
				check_internal(new_root);
			/*&&&&&&&&&&&&&&&&&&&&&& */

			/* do what is needed for buffer thrown from tree */
			reiserfs_invalidate_buffer(tb, tbSh);
			return;
		}
		return;
	}

	if (tb->L[h] && tb->lnum[h] == -B_NR_ITEMS(tb->L[h]) - 1) {	/* join S[h] with L[h] */

		RFALSE(tb->rnum[h] != 0,
		       "invalid tb->rnum[%d]==%d when joining S[h] with L[h]",
		       h, tb->rnum[h]);

		internal_shift_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h, n + 1);
		reiserfs_invalidate_buffer(tb, tbSh);

		return;
	}

	if (tb->R[h] && tb->rnum[h] == -B_NR_ITEMS(tb->R[h]) - 1) {	/* join S[h] with R[h] */
		RFALSE(tb->lnum[h] != 0,
		       "invalid tb->lnum[%d]==%d when joining S[h] with R[h]",
		       h, tb->lnum[h]);

		internal_shift_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h, n + 1);

		reiserfs_invalidate_buffer(tb, tbSh);
		return;
	}

	if (tb->lnum[h] < 0) {	/* borrow from left neighbor L[h] */
		RFALSE(tb->rnum[h] != 0,
		       "wrong tb->rnum[%d]==%d when borrow from L[h]", h,
		       tb->rnum[h]);
		/*internal_shift_right (tb, h, tb->L[h], tb->CFL[h], tb->lkey[h], tb->S[h], -tb->lnum[h]); */
		internal_shift_right(INTERNAL_SHIFT_FROM_L_TO_S, tb, h,
				     -tb->lnum[h]);
		return;
	}

	if (tb->rnum[h] < 0) {	/* borrow from right neighbor R[h] */
		RFALSE(tb->lnum[h] != 0,
		       "invalid tb->lnum[%d]==%d when borrow from R[h]",
		       h, tb->lnum[h]);
		internal_shift_left(INTERNAL_SHIFT_FROM_R_TO_S, tb, h, -tb->rnum[h]);	/*tb->S[h], tb->CFR[h], tb->rkey[h], tb->R[h], -tb->rnum[h]); */
		return;
	}

	if (tb->lnum[h] > 0) {	/* split S[h] into two parts and put them into neighbors */
		RFALSE(tb->rnum[h] == 0 || tb->lnum[h] + tb->rnum[h] != n + 1,
		       "invalid tb->lnum[%d]==%d or tb->rnum[%d]==%d when S[h](item number == %d) is split between them",
		       h, tb->lnum[h], h, tb->rnum[h], n);

		internal_shift_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h, tb->lnum[h]);	/*tb->L[h], tb->CFL[h], tb->lkey[h], tb->S[h], tb->lnum[h]); */
		internal_shift_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
				     tb->rnum[h]);

		reiserfs_invalidate_buffer(tb, tbSh);

		return;
	}
	reiserfs_panic(tb->tb_sb, "ibalance-2",
		       "unexpected tb->lnum[%d]==%d or tb->rnum[%d]==%d",
		       h, tb->lnum[h], h, tb->rnum[h]);
}