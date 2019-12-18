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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_journal_list {int /*<<< orphan*/  j_commit_left; } ;
struct reiserfs_journal {unsigned long j_trans_id; int j_errno; struct reiserfs_journal_list* j_current_jl; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_commit_list (struct super_block*,struct reiserfs_journal_list*,int) ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end_sync (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 scalar_t__ journal_list_still_alive (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  let_transaction_grow (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __commit_trans_jl(struct inode *inode, unsigned long id,
			     struct reiserfs_journal_list *jl)
{
	struct reiserfs_transaction_handle th;
	struct super_block *sb = inode->i_sb;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	int ret = 0;

	/* is it from the current transaction, or from an unknown transaction? */
	if (id == journal->j_trans_id) {
		jl = journal->j_current_jl;
		/* try to let other writers come in and grow this transaction */
		let_transaction_grow(sb, id);
		if (journal->j_trans_id != id) {
			goto flush_commit_only;
		}

		ret = journal_begin(&th, sb, 1);
		if (ret)
			return ret;

		/* someone might have ended this transaction while we joined */
		if (journal->j_trans_id != id) {
			reiserfs_prepare_for_journal(sb, SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&th, sb, SB_BUFFER_WITH_SB(sb));
			ret = journal_end(&th, sb, 1);
			goto flush_commit_only;
		}

		ret = journal_end_sync(&th, sb, 1);
		if (!ret)
			ret = 1;

	} else {
		/* this gets tricky, we have to make sure the journal list in
		 * the inode still exists.  We know the list is still around
		 * if we've got a larger transaction id than the oldest list
		 */
	      flush_commit_only:
		if (journal_list_still_alive(inode->i_sb, id)) {
			/*
			 * we only set ret to 1 when we know for sure
			 * the barrier hasn't been started yet on the commit
			 * block.
			 */
			if (atomic_read(&jl->j_commit_left) > 1)
				ret = 1;
			flush_commit_list(sb, jl, 1);
			if (journal->j_errno)
				ret = journal->j_errno;
		}
	}
	/* otherwise the list is gone, and long since committed */
	return ret;
}