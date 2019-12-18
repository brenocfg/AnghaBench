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
struct super_block {int s_flags; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_work; } ;
typedef  int /*<<< orphan*/  myth ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FLUSH_ALL ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * commit_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_journal_end (struct reiserfs_transaction_handle*,struct super_block*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_journal_ram (struct super_block*) ; 
 int /*<<< orphan*/  journal_join (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_join_abort (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ reiserfs_is_journal_aborted (struct reiserfs_journal*) ; 
 int /*<<< orphan*/  reiserfs_mounted_fs_count ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_journal_release(struct reiserfs_transaction_handle *th,
			      struct super_block *sb, int error)
{
	struct reiserfs_transaction_handle myth;
	int flushed = 0;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	/* we only want to flush out transactions if we were called with error == 0
	 */
	if (!error && !(sb->s_flags & MS_RDONLY)) {
		/* end the current trans */
		BUG_ON(!th->t_trans_id);
		do_journal_end(th, sb, 10, FLUSH_ALL);

		/* make sure something gets logged to force our way into the flush code */
		if (!journal_join(&myth, sb, 1)) {
			reiserfs_prepare_for_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, sb,
					   SB_BUFFER_WITH_SB(sb));
			do_journal_end(&myth, sb, 1, FLUSH_ALL);
			flushed = 1;
		}
	}

	/* this also catches errors during the do_journal_end above */
	if (!error && reiserfs_is_journal_aborted(journal)) {
		memset(&myth, 0, sizeof(myth));
		if (!journal_join_abort(&myth, sb, 1)) {
			reiserfs_prepare_for_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, sb,
					   SB_BUFFER_WITH_SB(sb));
			do_journal_end(&myth, sb, 1, FLUSH_ALL);
		}
	}

	reiserfs_mounted_fs_count--;
	/* wait for all commits to finish */
	cancel_delayed_work(&SB_JOURNAL(sb)->j_work);
	flush_workqueue(commit_wq);
	if (!reiserfs_mounted_fs_count) {
		destroy_workqueue(commit_wq);
		commit_wq = NULL;
	}

	free_journal_ram(sb);

	return 0;
}