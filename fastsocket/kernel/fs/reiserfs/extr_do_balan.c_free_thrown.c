#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int /*<<< orphan*/  transaction_handle; TYPE_1__** thrown; int /*<<< orphan*/  tb_sb; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;
struct TYPE_4__ {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 scalar_t__ buffer_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_free_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_thrown(struct tree_balance *tb)
{
	int i;
	b_blocknr_t blocknr;
	for (i = 0; i < ARRAY_SIZE(tb->thrown); i++) {
		if (tb->thrown[i]) {
			blocknr = tb->thrown[i]->b_blocknr;
			if (buffer_dirty(tb->thrown[i]))
				reiserfs_warning(tb->tb_sb, "reiserfs-12322",
						 "called with dirty buffer %d",
						 blocknr);
			brelse(tb->thrown[i]);	/* incremented in store_thrown */
			reiserfs_free_block(tb->transaction_handle, NULL,
					    blocknr, 0);
		}
	}
}