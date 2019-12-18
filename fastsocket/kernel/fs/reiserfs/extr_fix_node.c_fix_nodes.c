#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int* insert_size; int* blknum; int /*<<< orphan*/ ** FEB; int /*<<< orphan*/  tb_sb; int /*<<< orphan*/ ** CFR; int /*<<< orphan*/ ** CFL; int /*<<< orphan*/ ** FR; int /*<<< orphan*/ ** FL; int /*<<< orphan*/ ** R; int /*<<< orphan*/ ** L; TYPE_1__* tb_path; int /*<<< orphan*/  transaction_handle; int /*<<< orphan*/  fs_gen; } ;
struct item_head {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_fix_nodes; } ;
struct TYPE_7__ {int pos_in_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int CARRY_ON ; 
 int DC_SIZE ; 
 scalar_t__ FILESYSTEM_CHANGED_TB (struct tree_balance*) ; 
 int KEY_SIZE ; 
 int MAX_FEB_SIZE ; 
 int MAX_HEIGHT ; 
#define  M_CUT 131 
#define  M_DELETE 130 
#define  M_INSERT 129 
#define  M_PASTE 128 
 int NO_BALANCING_NEEDED ; 
 int /*<<< orphan*/  PATH_H_PBUFFER (TYPE_1__*,int) ; 
 int PATH_LAST_POSITION (TYPE_1__*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (TYPE_1__*) ; 
 TYPE_3__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 int REPEAT_SEARCH ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int check_balance (int,struct tree_balance*,int,int,int,struct item_head*,void const*) ; 
 scalar_t__ cur_tb ; 
 int get_direct_parent (struct tree_balance*,int) ; 
 int get_empty_nodes (struct tree_balance*,int) ; 
 int /*<<< orphan*/  get_generation (int /*<<< orphan*/ ) ; 
 int get_mem_for_virtual_node (struct tree_balance*) ; 
 int get_neighbors (struct tree_balance*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathrelse (TYPE_1__*) ; 
 int /*<<< orphan*/  pathrelse_and_restore (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  print_block (struct buffer_head*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_cur_tb (char*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_tb_buffers_until_unlocked (struct tree_balance*) ; 

int fix_nodes(int op_mode, struct tree_balance *tb,
	      struct item_head *ins_ih, const void *data)
{
	int ret, h, item_num = PATH_LAST_POSITION(tb->tb_path);
	int pos_in_item;

	/* we set wait_tb_buffers_run when we have to restore any dirty bits cleared
	 ** during wait_tb_buffers_run
	 */
	int wait_tb_buffers_run = 0;
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);

	++REISERFS_SB(tb->tb_sb)->s_fix_nodes;

	pos_in_item = tb->tb_path->pos_in_item;

	tb->fs_gen = get_generation(tb->tb_sb);

	/* we prepare and log the super here so it will already be in the
	 ** transaction when do_balance needs to change it.
	 ** This way do_balance won't have to schedule when trying to prepare
	 ** the super for logging
	 */
	reiserfs_prepare_for_journal(tb->tb_sb,
				     SB_BUFFER_WITH_SB(tb->tb_sb), 1);
	journal_mark_dirty(tb->transaction_handle, tb->tb_sb,
			   SB_BUFFER_WITH_SB(tb->tb_sb));
	if (FILESYSTEM_CHANGED_TB(tb))
		return REPEAT_SEARCH;

	/* if it possible in indirect_to_direct conversion */
	if (buffer_locked(tbS0)) {
		__wait_on_buffer(tbS0);
		if (FILESYSTEM_CHANGED_TB(tb))
			return REPEAT_SEARCH;
	}
#ifdef CONFIG_REISERFS_CHECK
	if (cur_tb) {
		print_cur_tb("fix_nodes");
		reiserfs_panic(tb->tb_sb, "PAP-8305",
			       "there is pending do_balance");
	}

	if (!buffer_uptodate(tbS0) || !B_IS_IN_TREE(tbS0))
		reiserfs_panic(tb->tb_sb, "PAP-8320", "S[0] (%b %z) is "
			       "not uptodate at the beginning of fix_nodes "
			       "or not in tree (mode %c)",
			       tbS0, tbS0, op_mode);

	/* Check parameters. */
	switch (op_mode) {
	case M_INSERT:
		if (item_num <= 0 || item_num > B_NR_ITEMS(tbS0))
			reiserfs_panic(tb->tb_sb, "PAP-8330", "Incorrect "
				       "item number %d (in S0 - %d) in case "
				       "of insert", item_num,
				       B_NR_ITEMS(tbS0));
		break;
	case M_PASTE:
	case M_DELETE:
	case M_CUT:
		if (item_num < 0 || item_num >= B_NR_ITEMS(tbS0)) {
			print_block(tbS0, 0, -1, -1);
			reiserfs_panic(tb->tb_sb, "PAP-8335", "Incorrect "
				       "item number(%d); mode = %c "
				       "insert_size = %d",
				       item_num, op_mode,
				       tb->insert_size[0]);
		}
		break;
	default:
		reiserfs_panic(tb->tb_sb, "PAP-8340", "Incorrect mode "
			       "of operation");
	}
#endif

	if (get_mem_for_virtual_node(tb) == REPEAT_SEARCH)
		// FIXME: maybe -ENOMEM when tb->vn_buf == 0? Now just repeat
		return REPEAT_SEARCH;

	/* Starting from the leaf level; for all levels h of the tree. */
	for (h = 0; h < MAX_HEIGHT && tb->insert_size[h]; h++) {
		ret = get_direct_parent(tb, h);
		if (ret != CARRY_ON)
			goto repeat;

		ret = check_balance(op_mode, tb, h, item_num,
				    pos_in_item, ins_ih, data);
		if (ret != CARRY_ON) {
			if (ret == NO_BALANCING_NEEDED) {
				/* No balancing for higher levels needed. */
				ret = get_neighbors(tb, h);
				if (ret != CARRY_ON)
					goto repeat;
				if (h != MAX_HEIGHT - 1)
					tb->insert_size[h + 1] = 0;
				/* ok, analysis and resource gathering are complete */
				break;
			}
			goto repeat;
		}

		ret = get_neighbors(tb, h);
		if (ret != CARRY_ON)
			goto repeat;

		/* No disk space, or schedule occurred and analysis may be
		 * invalid and needs to be redone. */
		ret = get_empty_nodes(tb, h);
		if (ret != CARRY_ON)
			goto repeat;

		if (!PATH_H_PBUFFER(tb->tb_path, h)) {
			/* We have a positive insert size but no nodes exist on this
			   level, this means that we are creating a new root. */

			RFALSE(tb->blknum[h] != 1,
			       "PAP-8350: creating new empty root");

			if (h < MAX_HEIGHT - 1)
				tb->insert_size[h + 1] = 0;
		} else if (!PATH_H_PBUFFER(tb->tb_path, h + 1)) {
			if (tb->blknum[h] > 1) {
				/* The tree needs to be grown, so this node S[h]
				   which is the root node is split into two nodes,
				   and a new node (S[h+1]) will be created to
				   become the root node.  */

				RFALSE(h == MAX_HEIGHT - 1,
				       "PAP-8355: attempt to create too high of a tree");

				tb->insert_size[h + 1] =
				    (DC_SIZE +
				     KEY_SIZE) * (tb->blknum[h] - 1) +
				    DC_SIZE;
			} else if (h < MAX_HEIGHT - 1)
				tb->insert_size[h + 1] = 0;
		} else
			tb->insert_size[h + 1] =
			    (DC_SIZE + KEY_SIZE) * (tb->blknum[h] - 1);
	}

	ret = wait_tb_buffers_until_unlocked(tb);
	if (ret == CARRY_ON) {
		if (FILESYSTEM_CHANGED_TB(tb)) {
			wait_tb_buffers_run = 1;
			ret = REPEAT_SEARCH;
			goto repeat;
		} else {
			return CARRY_ON;
		}
	} else {
		wait_tb_buffers_run = 1;
		goto repeat;
	}

      repeat:
	// fix_nodes was unable to perform its calculation due to
	// filesystem got changed under us, lack of free disk space or i/o
	// failure. If the first is the case - the search will be
	// repeated. For now - free all resources acquired so far except
	// for the new allocated nodes
	{
		int i;

		/* Release path buffers. */
		if (wait_tb_buffers_run) {
			pathrelse_and_restore(tb->tb_sb, tb->tb_path);
		} else {
			pathrelse(tb->tb_path);
		}
		/* brelse all resources collected for balancing */
		for (i = 0; i < MAX_HEIGHT; i++) {
			if (wait_tb_buffers_run) {
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->L[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->R[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->FL[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->FR[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->
								 CFL[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->
								 CFR[i]);
			}

			brelse(tb->L[i]);
			brelse(tb->R[i]);
			brelse(tb->FL[i]);
			brelse(tb->FR[i]);
			brelse(tb->CFL[i]);
			brelse(tb->CFR[i]);

			tb->L[i] = NULL;
			tb->R[i] = NULL;
			tb->FL[i] = NULL;
			tb->FR[i] = NULL;
			tb->CFL[i] = NULL;
			tb->CFR[i] = NULL;
		}

		if (wait_tb_buffers_run) {
			for (i = 0; i < MAX_FEB_SIZE; i++) {
				if (tb->FEB[i])
					reiserfs_restore_prepared_buffer
					    (tb->tb_sb, tb->FEB[i]);
			}
		}
		return ret;
	}

}