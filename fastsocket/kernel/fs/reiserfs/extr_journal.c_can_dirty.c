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
struct super_block {int dummy; } ;
struct reiserfs_journal_cnode {scalar_t__ blocknr; struct reiserfs_journal_cnode* hnext; struct super_block* sb; scalar_t__ bh; TYPE_1__* jlist; struct reiserfs_journal_cnode* hprev; } ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_2__ {scalar_t__ j_len; int /*<<< orphan*/  j_commit_left; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int can_dirty(struct reiserfs_journal_cnode *cn)
{
	struct super_block *sb = cn->sb;
	b_blocknr_t blocknr = cn->blocknr;
	struct reiserfs_journal_cnode *cur = cn->hprev;
	int can_dirty = 1;

	/* first test hprev.  These are all newer than cn, so any node here
	 ** with the same block number and dev means this node can't be sent
	 ** to disk right now.
	 */
	while (cur && can_dirty) {
		if (cur->jlist && cur->bh && cur->blocknr && cur->sb == sb &&
		    cur->blocknr == blocknr) {
			can_dirty = 0;
		}
		cur = cur->hprev;
	}
	/* then test hnext.  These are all older than cn.  As long as they
	 ** are committed to the log, it is safe to write cn to disk
	 */
	cur = cn->hnext;
	while (cur && can_dirty) {
		if (cur->jlist && cur->jlist->j_len > 0 &&
		    atomic_read(&(cur->jlist->j_commit_left)) > 0 && cur->bh &&
		    cur->blocknr && cur->sb == sb && cur->blocknr == blocknr) {
			can_dirty = 0;
		}
		cur = cur->hnext;
	}
	return can_dirty;
}