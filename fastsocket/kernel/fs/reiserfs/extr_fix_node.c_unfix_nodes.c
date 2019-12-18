#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int /*<<< orphan*/  vn_buf; TYPE_1__** used; int /*<<< orphan*/  transaction_handle; TYPE_1__** FEB; TYPE_1__** CFR; TYPE_1__** CFL; TYPE_1__** FR; TYPE_1__** FL; TYPE_1__** R; TYPE_1__** L; int /*<<< orphan*/  tb_sb; int /*<<< orphan*/  tb_path; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int MAX_FEB_SIZE ; 
 int MAX_HEIGHT ; 
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathrelse_and_restore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_free_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (int /*<<< orphan*/ ,TYPE_1__*) ; 

void unfix_nodes(struct tree_balance *tb)
{
	int i;

	/* Release path buffers. */
	pathrelse_and_restore(tb->tb_sb, tb->tb_path);

	/* brelse all resources collected for balancing */
	for (i = 0; i < MAX_HEIGHT; i++) {
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->L[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->R[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->FL[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->FR[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->CFL[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->CFR[i]);

		brelse(tb->L[i]);
		brelse(tb->R[i]);
		brelse(tb->FL[i]);
		brelse(tb->FR[i]);
		brelse(tb->CFL[i]);
		brelse(tb->CFR[i]);
	}

	/* deal with list of allocated (used and unused) nodes */
	for (i = 0; i < MAX_FEB_SIZE; i++) {
		if (tb->FEB[i]) {
			b_blocknr_t blocknr = tb->FEB[i]->b_blocknr;
			/* de-allocated block which was not used by balancing and
			   bforget about buffer for it */
			brelse(tb->FEB[i]);
			reiserfs_free_block(tb->transaction_handle, NULL,
					    blocknr, 0);
		}
		if (tb->used[i]) {
			/* release used as new nodes including a new root */
			brelse(tb->used[i]);
		}
	}

	kfree(tb->vn_buf);

}